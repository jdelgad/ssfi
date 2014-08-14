/*
 * file_locator.h
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#ifndef FILE_LOCATOR_H_
#define FILE_LOCATOR_H_

#include <memory>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include "parser.h"
#include "worker_queue.h"

namespace solidfire
{

class FileLocator
{
    public:
        // the file type to look for (".txt" or ".json" files) and the worker
        // pool used to parse in data
        FileLocator(const std::string &file_extension,
                    const std::shared_ptr<WorkerQueue> &worker_queue_ptr);

        void recursively_find_files(const boost::filesystem::path &path);

        // need to return a std::move reference since the Parser class has a
        // boost::mutex data member
        Parser&& get_parser();

#ifdef SOLIDFIRE_TESTING
        std::vector<std::string> get_files() const;
#endif
    private:
        FileLocator() = delete;
        FileLocator(FileLocator &) = delete;
        FileLocator(FileLocator &&) = delete;
        FileLocator& operator=(FileLocator &) = delete;
        FileLocator&& operator=(FileLocator &&) = delete;

#ifdef SOLIDFIRE_TESTING
        std::vector<std::string> m_files_found;
#endif
        std::string m_file_extension;
        std::shared_ptr<WorkerQueue> m_worker_queue_ptr;
        Parser m_parser;
};

}
#endif /* FILE_LOCATOR_H_ */
