/*
 * parser.cpp
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#include "parser.h"

#include <fstream>
#include <string>
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

void Parser::merge_data(const std::map<std::string, int> word_count_map)
{
    BOOST_LOG_TRIVIAL(trace) << "Parser::merge_data()";

    std::lock_guard<std::mutex> lock(m_mutex);

    for (auto &iter : word_count_map)
    {
        std::cout << iter.first << " " << iter.second << std::endl;
    }

}

std::map<std::string, int> Parser::get_word_count_map()
{
    BOOST_LOG_TRIVIAL(trace) << "Parser::get_word_count_map()";
    return m_word_count_map;
}
