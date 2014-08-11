/*
 * worker.cpp
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#include "worker.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

void foo() {
}

Worker::Worker(int number_of_threads)
 : m_num_threads(number_of_threads),
   m_work_ptr(nullptr)
{
    m_work_ptr = std::make_shared<boost::asio::io_service::work>(io_service);
}

Worker::~Worker()
{
    m_work_ptr.reset();
}

void Worker::join_all()
{
    m_threads.join_all();
}

void Worker::spawn_threads()
{
    for (int i = 0; i < m_num_threads; ++i)
    {
        m_threads.create_thread(boost::bind(&boost::asio::io_service::run,
                &io_service));
    }
}

void Worker::add_task()
{
    io_service.post(boost::bind(foo));
}

