#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>

#include "file_locator.h"
#include "worker.h"

void check_directory(const boost::filesystem::path &path)
// check the file system path and if it's not a file or symbolic link it must
// be a directory
{
    if (boost::filesystem::exists(path))
    {
        if (boost::filesystem::is_regular_file(path))
        {
            std::cerr << path << "ERROR: passed in argument is a file, not a "
                      << "directory (" << path << ")" << std::endl;
            exit(-1);
        }
        else if (!boost::filesystem::is_directory(path))
        {
            std::cerr << "ERROR: passed in argument is neither a file or a "
                      << "directory path (" << path << ")" << std::endl;
            exit(-1);
        }
        // else it is a directory
    }
    else
    {
        std::cerr << "ERROR: passed in argument does not exist in the "
                  << "file system (" << path << ")" << std::endl;
        exit(-1);
    }
}

void parse_args(int argc, char *argv[], int &N, std::string &path)
// parse the arguments passed in to the program and based on the flags used
// the number_of_threads and directory vars should be set properly if this
// returns; the system exits if an error occurs
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "Display help message")
            ("dir,d",
             boost::program_options::value<std::string>(&path)->required(),
             "Directory to search for text files")
            ("N", boost::program_options::value<int>(&N)->default_value(3),
             "The number of threads to parse the text files");

    boost::program_options::variables_map variables_map;

    try
    {
        boost::program_options::store( boost::program_options::parse_command_line(argc, argv, desc),
                variables_map);

        if (variables_map.count("help"))
        {
            std::cout << desc << std::endl;
            exit(0);
        }

        boost::program_options::notify(variables_map);
    } catch (const boost::program_options::error &e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        exit(-1);
    }

    if (N <= 0)
    {
        std::cerr << "ERROR: -N argument must be greater than or equal to 1"
                  << std::endl;
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    int number_of_threads{0};
    std::string directory;

    parse_args(argc, argv, number_of_threads, directory);

    boost::filesystem::path path(directory);

    check_directory(path);

    BOOST_LOG_TRIVIAL(info) << "Finding text files under " << directory;
    BOOST_LOG_TRIVIAL(info) << "Number of worker threads to read in text "
                            << "files: " << number_of_threads;


    Worker worker_threads{number_of_threads};
    FileLocator file_locator{".txt"};

    // Requirement 1: start up a thread to find all of the files passed in via
    // a command line argument
    boost::thread find_files(&FileLocator::recursively_find_files,
            &file_locator, path);

    find_files.join();
    return 0;
}
