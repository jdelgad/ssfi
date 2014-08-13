/*
 * parser.h
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <map>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

class Parser
{
    public:
        Parser() = default;
        Parser(Parser&&) = default;

        void parse_file(boost::filesystem::path path);

        std::map<std::string, int> get_word_count_map();
        std::multimap<int, std::string> get_count_word_map();

    private:
        // don't need to pass by const value due to std::move for std::map
        void merge_data(std::map<std::string, int> word_count_map);
        boost::mutex m_mutex;
        std::map<std::string, int> m_word_count_map;
};




#endif /* PARSER_H_ */
