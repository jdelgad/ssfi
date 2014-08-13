/*
 * file_locator.h
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#ifndef FILE_LOCATOR_H_
#define FILE_LOCATOR_H_

#include <string>

#include <boost/filesystem.hpp>

#include "worker_queue.h"

#include <string>
#include <memory>
#include <boost/filesystem/path.hpp>

#include "parser.h"

class FileLocator
{
    public:
        FileLocator(const std::string &file_extension,
                    const std::shared_ptr<WorkerQueue> &worker_queue_ptr);
        void recursively_find_files(const boost::filesystem::path &path);

        Parser&& get_parser();
    private:
        FileLocator() = delete;
        FileLocator(FileLocator &) = delete;
        FileLocator(FileLocator &&) = delete;
        FileLocator& operator=(FileLocator &) = delete;
        FileLocator&& operator=(FileLocator &&) = delete;

        std::string m_file_extension;
        std::shared_ptr<WorkerQueue> m_worker_queue_ptr;
        Parser m_parser;
};

#endif /* FILE_LOCATOR_H_ */
