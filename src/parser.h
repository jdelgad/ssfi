/*
 * parser.h
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <map>
#include <mutex>
#include <string>

#include <boost/filesystem.hpp>

class Parser
{
    public:
        Parser() = default;
        Parser(Parser&&) = default;

        void parse_file(boost::filesystem::path path);

        std::map<std::string, int> get_word_count_map();

    private:

        void merge_data(const std::map<std::string, int> word_count_map);
        std::mutex m_mutex;
        std::map<std::string, int> m_word_count_map;
        std::map<int, std::vector<std::string>> m_count_word_map;
};




#endif /* PARSER_H_ */
