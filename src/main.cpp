#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include <boost/filesystem.hpp>

void check_directory(const boost::filesystem::path &path)
{
    if (boost::filesystem::exists(path))
    {
      if (boost::filesystem::is_regular_file(path))
      {
        std::cout << path << " size is " << boost::filesystem::file_size(path) << '\n';
      }

      else if (boost::filesystem::is_directory(path))
      {
        std::cout << path << " is a directory\n";
      }
      else
      {
        std::cout << path << " exists, but is neither a regular file nor a directory\n";
      }
    }
    else
    {
      std::cout << path << " does not exist\n";
    }
}

std::string parse_args(const std::vector<std::string> &arguments)
{
    if (arguments.size() != 1)
    {
        std::cerr << "Invalid number of arguments passed in" << std::endl;
        std::cerr << "Expected 1 argument, received "
                  << arguments.size() << " arguments " << std::endl;
        exit(-1);
    }

    return arguments.at(0);
}

int main(int argc, char *argv[])
{

    std::vector<std::string> arguments(argv + 1, argv + argc);

    boost::filesystem::path path(parse_args(arguments));

    check_directory(path);


    return 0;
}
