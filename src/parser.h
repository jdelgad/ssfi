/*
 * parser.h
 *
 *  Created on: Aug 10, 2014
 *      Author: Jacob Delgado
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <map>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>

namespace ssfi
{

class Parser
{
    public:
        Parser() = default;
        Parser(Parser&&) = default;
        Parser& operator=(Parser &&) = default;

        void parse_file(boost::filesystem::path path);

        std::map<std::string, int> get_word_count_map() const;

        // transform m_word_count_map (k,v) pair into a multimap of (v,k)
        std::multimap<int, std::string> get_count_word_map();

    private:
        // due to boost::mutex, these are already implicity deleted
        Parser(Parser&) = delete;
        Parser& operator=(Parser&) = delete;

        // don't need to pass by const value due to std::move for std::map
        void merge_data(std::map<std::string, int> word_count_map);

        boost::mutex m_mutex;
        std::map<std::string, int> m_word_count_map;

        // define a regex for every instance of this class; use perl regexes
        // and ignore case sensitivity
        boost::regex m_re = boost::regex("[\\w|\\d]+",boost::regex::perl|boost::regex::icase);
};

}

#endif /* PARSER_H_ */
