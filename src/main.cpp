#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>

#include <cstdlib>

#include "file_locator.h"
#include "worker_queue.h"
#include "boost_asio_queue.h"

namespace ssfi {

void print_top_words(int num, std::multimap<int, std::string> count_word_map)
// since std::map sorts by std::less on keys and the key is of type integer
// by getting the end of the map and iterating backward we can find the
// largest word counts for each word
{
    auto iter = count_word_map.rbegin();
    for (int i = 1; i <= num && iter != count_word_map.rend(); ++i, ++iter)
    {
        std::cout << i << ") " << iter->second << ": " << iter->first << std::endl;
    }
}

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
            ("verbose,v", "Increase verbosity")
            ("dir,d", boost::program_options::value<std::string>(&path)->required(),
             "Directory to search for text files")
            ("N", boost::program_options::value<int>(&N)->default_value(3),
             "The number of threads to parse the text files");

    boost::program_options::variables_map variables_map;

    try
    {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc),
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

    if (variables_map.count("verbose"))
    {
        boost::log::core::get()->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::trace);
    }
    else
    {
        boost::log::core::get()->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::info);
    }
}

};

int main(int argc, char *argv[])
{
    int number_of_threads{0};
    std::string directory;

    ssfi::parse_args(argc, argv, number_of_threads, directory);

    boost::filesystem::path path(directory);

    ssfi::check_directory(path);

    BOOST_LOG_TRIVIAL(info) << "Finding text files under " << directory;
    BOOST_LOG_TRIVIAL(info) << "Number of worker threads to read in text "
                            << "files: " << number_of_threads;

    //std::shared_ptr<WorkerQueue> worker_queue_ptr =
    auto worker_queue_ptr =
            std::make_shared<ssfi::BoostAsIOQueue>(number_of_threads);
    worker_queue_ptr->spawn_threads();

    ssfi::FileLocator file_locator{".txt", worker_queue_ptr};

    // Requirement 2: start up a thread to find all of the files passed in via
    // a command line argument
    boost::thread find_files(&ssfi::FileLocator::recursively_find_files,
            &file_locator, path);

    find_files.join();
    worker_queue_ptr->clear();
    worker_queue_ptr->join();

    BOOST_LOG_TRIVIAL(trace) << "Worker queue finished";

    const auto count_word_map = file_locator.get_parser().get_count_word_map();

    BOOST_LOG_TRIVIAL(trace) << "length of map = " << count_word_map.size();

    ssfi::print_top_words(10, count_word_map);

    return 0;
}
