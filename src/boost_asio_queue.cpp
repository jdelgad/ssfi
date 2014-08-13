/*
 * worker.cpp
 *
 *  Created on: Aug 10, 2014
 *      Author: jdelgad
 */

#include "boost_asio_queue.h"

#include <boost/log/trivial.hpp>

void foo() {
}

BoostAsIOQueue::BoostAsIOQueue(int number_of_threads)
 : WorkerQueue(number_of_threads),
   m_work_ptr(nullptr)
{
    m_work_ptr = std::make_shared<boost::asio::io_service::work>(m_io_service);
}

BoostAsIOQueue::~BoostAsIOQueue()
{
}

void BoostAsIOQueue::spawn()
{
    BOOST_LOG_TRIVIAL(trace) << "BoostAsIOQueue::spawn()";
    for (int i = 0; i < get_number_of_threads(); ++i)
    {
        m_threads.create_thread(boost::bind(&boost::asio::io_service::run,
                &m_io_service));
    }
}

void BoostAsIOQueue::add_task(boost::function<void(void)> task)
{
    BOOST_LOG_TRIVIAL(trace) << "BoostAsIOQueue::add_task()";
    m_io_service.post(task);
}

void BoostAsIOQueue::join_all()
{
    BOOST_LOG_TRIVIAL(trace) << "BoostAsIOQueue::join_all()";
    m_threads.join_all();
}

void BoostAsIOQueue::reset()
{
    BOOST_LOG_TRIVIAL(trace) << "BoostAsIOQueue::reset()";
    m_work_ptr.reset();
}

void BoostAsIOQueue::quit()
{
    BOOST_LOG_TRIVIAL(trace) << "BoostAsIOQueue::quit()";
    m_io_service.stop();
}

