/*
 * worker_queue.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: Jacob Delgado
 */

#include "worker_queue.h"

#include <boost/log/trivial.hpp>

namespace ssfi
{

WorkerQueue::WorkerQueue(int number_of_threads)
  : m_num_threads(number_of_threads)
{

}

WorkerQueue::~WorkerQueue()
{

}

int WorkerQueue::get_number_of_threads() const
{
    return m_num_threads;
}

void WorkerQueue::spawn_threads()
{
    BOOST_LOG_TRIVIAL(trace) << "WorkerQueue::spawn_threads()";
    spawn();
}

void WorkerQueue::add(boost::function<void(void)> task)
{
    BOOST_LOG_TRIVIAL(trace) << "WorkerQueue::add()";
    add_task(task);
}

void WorkerQueue::join()
{
    BOOST_LOG_TRIVIAL(trace) << "WorkerQueue::join()";
    join_all();
}

void WorkerQueue::clear()
{
    BOOST_LOG_TRIVIAL(trace) << "WorkerQueue::clear()";
    reset();
}

void WorkerQueue::stop()
{
    BOOST_LOG_TRIVIAL(trace) << "WorkerQueue::stop()";
    quit();
}

}
