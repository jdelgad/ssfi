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

FileLocator::FileLocator(const std::string &file_extension,
        const std::shared_ptr<WorkerQueue> &worker_queue_ptr)
  : m_file_extension(file_extension),
    m_worker_queue_ptr(worker_queue_ptr)
{
    assert(file_extension.length() == 4 && file_extension[0] == '.');
    assert(worker_queue_ptr != nullptr);
}

void FileLocator::recursively_find_files(const boost::filesystem::path &path)
{
    BOOST_LOG_TRIVIAL(trace) << "FileLocator::recursively_find_files()";
    boost::filesystem::recursive_directory_iterator dir_iter(path);
    boost::filesystem::recursive_directory_iterator end_iter;

    for ( ; dir_iter != end_iter; ++dir_iter)
    {
        if (dir_iter->path().extension() == ".txt")
        {
            boost::filesystem::path path = dir_iter->path();
            BOOST_LOG_TRIVIAL(info) << "Found " << path;
            m_worker_queue_ptr->add(boost::bind(&Parser::parse_file, &m_parser, path));
        }
    }
}

Parser&& FileLocator::get_parser()
{
    BOOST_LOG_TRIVIAL(trace) << "FileLocator::get_parser()";
    return std::move(m_parser);
}
