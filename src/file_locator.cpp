/*
 * file_locator.cpp
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#include "file_locator.h"

#include <cassert>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

FileLocator::FileLocator(const std::string &file_extension)
  : m_file_extension(file_extension)
{
    assert(file_extension.length() == 4 && file_extension[0] == '.');
}

void FileLocator::recursively_find_files(const boost::filesystem::path &path) const
{
    boost::filesystem::recursive_directory_iterator dir_iter(path);
    boost::filesystem::recursive_directory_iterator end_iter;

    for ( ; dir_iter != end_iter; ++dir_iter)
    {
        if (dir_iter->path().extension() == ".txt")
        {
            BOOST_LOG_TRIVIAL(info) << "Found " << dir_iter->path();
        }
    }
}
