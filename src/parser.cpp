/*
 * parser.cpp
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#include "parser.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <boost/log/trivial.hpp>
#include <boost/regex.hpp>

namespace solidfire
{

void Parser::parse_file(boost::filesystem::path path)

{
    BOOST_LOG_TRIVIAL(trace) << "Parser::parse_file()";
    std::ifstream ifile(path.string());
    std::map<std::string, int> word_count;
    std::string word;
    std::vector<std::string> string_vector;

    if (!ifile.good())
      return;

    while (ifile >> word)
    {
        //std::cout << "word = " << word << std::endl;
        boost::sregex_token_iterator current_word_iter(word.begin(), word.end(), m_re, 0);
        boost::sregex_token_iterator last_word_iter;
        while (current_word_iter != last_word_iter)
        {
            BOOST_LOG_TRIVIAL(trace) << "Parsing word " << *current_word_iter;

            // make a copy of the word we tokenized and then transfer it to
            // lowercase only
            std::string lowercase_cw = *current_word_iter;
            std::transform(lowercase_cw.begin(), lowercase_cw.end(),
                           lowercase_cw.begin(), ::tolower);

            if (word_count.count(lowercase_cw))
            {
                ++word_count[lowercase_cw];
            }
            else
            {
                word_count[lowercase_cw] = 1;
            }

            ++current_word_iter;
        }
    }

    // since this is shared data across multiple threads, use a different
    // function and note the lock_guard clause
    merge_data(word_count);
}

void Parser::merge_data(std::map<std::string, int> word_count_map)
// merges the existing data map with new data read in; uses lock_guard for
// the entire enclosing function
{
    BOOST_LOG_TRIVIAL(trace) << "Parser::merge_data()";

    boost::lock_guard<boost::mutex> lock(m_mutex);

    for (auto &wc_map : word_count_map)
    {
        if (m_word_count_map.count(wc_map.first))
        {
            m_word_count_map[wc_map.first] += wc_map.second;
        }
        else
        {
            m_word_count_map[wc_map.first] = wc_map.second;
        }
    }

    BOOST_LOG_TRIVIAL(trace) << "length of map is now = " << m_word_count_map.size();
}

std::map<std::string, int> Parser::get_word_count_map() const
{
    BOOST_LOG_TRIVIAL(trace) << "Parser::get_word_count_map()";
    return m_word_count_map;
}

std::multimap<int, std::string> Parser::get_count_word_map()
{
    BOOST_LOG_TRIVIAL(trace) << "Parser::get_count_word_map()";
    std::multimap<int, std::string> count_word_map;

    // reverse the k,v pair in m_word_count_map
    std::transform(m_word_count_map.begin(), m_word_count_map.end(),
        std::inserter(count_word_map, count_word_map.begin()),
        [](std::pair<const std::string, int> &p) {
            return std::pair<int,std::string>(p.second, p.first);
    });

    return count_word_map;
}

}
