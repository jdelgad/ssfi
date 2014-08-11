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

#include "worker.h"

class FileLocator
{
    public:
        FileLocator(const std::string &file_extension);
        void recursively_find_files(const boost::filesystem::path &path) const;
    private:
        FileLocator() = delete;
        FileLocator(FileLocator &) = delete;
        FileLocator(FileLocator &&) = delete;
        FileLocator& operator=(FileLocator &) = delete;
        FileLocator&& operator=(FileLocator &&) = delete;

        std::string m_file_extension;
};



#endif /* FILE_LOCATOR_H_ */
