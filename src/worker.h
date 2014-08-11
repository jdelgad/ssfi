/*
 * worker.h
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class Worker
{
    public:
        explicit Worker(int number_of_threads);

        void spawn_threads();
        void add_task();
        void join_all();

        ~Worker();

    private:
        Worker() = delete;

        int m_num_threads;
        boost::asio::io_service io_service;
        boost::thread_group m_threads;
        std::shared_ptr<boost::asio::io_service::work> m_work_ptr;
};




#endif /* WORKER_H_ */
