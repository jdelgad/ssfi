/*
 * test_file_locator.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: Jacob Delgado
 */

#include "parser.h"

#include <boost/filesystem.hpp>

int main()
{
    std::vector<boost::filesystem::path> files{"unit_test/files/animal/dog/billie.txt",
                                               "unit_test/files/animal/bird/tweety.txt",
                                               "unit_test/files/foo/bar/foobar.txt"};

    ssfi::Parser parser;

    for (auto &f : files)
    {
        parser.parse_file(f);
    }

    auto word_count_map = parser.get_word_count_map();
    auto count_word_map = parser.get_count_word_map();

    assert(word_count_map["computer"] == 4);
    assert(word_count_map["science"] == 3);
    assert(word_count_map["is"] == 2);
    assert(word_count_map["tweety"] == 2);

    std::cout << "Testing passed" << std::endl;
    return 0;
}
