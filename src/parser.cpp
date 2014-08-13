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

void Parser::parse_file(boost::filesystem::path path)
{
    BOOST_LOG_TRIVIAL(trace) << "Parser::parse_file()";
    std::ifstream ifile(path.string());
    std::map<std::string, int> word_count;
    std::string word;

    if (!ifile.good())
      return;

    while (ifile >> word)
    {
        if (word_count.count(word))
        {
            ++word_count[word];
        }
        else
        {
            word_count[word] = 1;
        }
    }

    merge_data(word_count);
}

void Parser::merge_data(std::map<std::string, int> word_count_map)
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
