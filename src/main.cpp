#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

void check_directory(const boost::filesystem::path &path)
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
                  << "filesystem (" << path << ")" << std::endl;
        exit(-1);
    }
}

void parse_args(int argc, char *argv[], int &N, std::string &path)
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
        boost::program_options::store(
                boost::program_options::parse_command_line(argc, argv, desc),
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

    std::cout << "N = " << N << std::endl;
    std::cout << "directory = " << path << std::endl;
}

int main(int argc, char *argv[])
{
    int number_of_threads{0};
    std::string directory;

    parse_args(argc, argv, number_of_threads, directory);

    boost::filesystem::path path(directory);

    check_directory(path);

    return 0;
}
