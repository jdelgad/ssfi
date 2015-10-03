/*
 * test_file_locator.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: Jacob Delgado
 */

#include "worker_queue.h"
#include "file_locator.h"
#include "mock_worker_queue.h"

#include <algorithm>
#include <boost/filesystem.hpp>

int main()
{
    int number_of_threads{0};
    boost::filesystem::path path("unit_test/files/");
    std::shared_ptr<ssfi::WorkerQueue> worker_queue_ptr =
            std::make_shared<ssfi::MockWorkerQueue>(number_of_threads);
    ssfi::FileLocator file_locator(".txt", worker_queue_ptr);
    file_locator.recursively_find_files(path);

    std::vector<std::string> files{"unit_test/files/animal/dog/billie.txt",
                                   "unit_test/files/animal/bird/tweety.txt",
                                   "unit_test/files/foo/bar/foobar.txt"};

    const auto found_files = file_locator.get_files();
    assert(files.size() == 3);
    assert(std::is_permutation(files.begin(), files.end(), found_files.begin()));

    std::cout << "Testing passed" << std::endl;
    return 0;
}
