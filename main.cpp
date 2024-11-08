#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>
#include <libavutil/mem.h>

#include "calclum.h"

int main(int arg, char** args)
{ 
    //check # of arguments
    if(arg < 2)
    {
        std::cout << "Invalid number of arguments.\n";
        return 1;
    }

    //check if directory is valid
    std::filesystem::path path{args[1]};
    if(std::filesystem::exists(path) == false)
    {
        std::cout << "Path not found.\n";
        return 1;
    }

    //build up the files for processing
    std::vector<std::string> files;
    for(const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if(entry.is_regular_file())
        {
            files.push_back(entry.path().string());
        }
    }

    if(files.size() <= 0)
    {
        std::cout << "No files found.\n";
        return 1;
    }

    //get # of threads to run
    auto threadcount = std::thread::hardware_concurrency();
    if(arg >= 3)
    {
        threadcount = std::stoi(args[2]);
    }

    calclum calc(files, threadcount);
    return calc.run();
}
