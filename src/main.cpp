#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sys/stat.h>

void check_directory(const std::string &dir)
{
    struct stat st;

    const char *directory = dir.c_str();

    if (stat(directory, &st) != 0)
    {
        std::cerr << "ERROR: Directory argument " << dir
                  << " does not exist" << std::endl;
        exit(-1);
    }
    if (S_ISDIR(st.st_mode) == 0)
    {
        std::cerr << "ERROR: Argument " << dir
                  << " passed in is not a directory" << std::endl;
        exit(-1);
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

    const std::string directory = parse_args(arguments);

    check_directory(directory);


    return 0;
}
