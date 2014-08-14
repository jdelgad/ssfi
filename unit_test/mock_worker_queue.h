/*
 * mock_worker_queue.h
 *
 * Class created to mock a worker queue so that we can test it in a single
 * thread and not a thread pool since debugging with a multithreaded app can be
 * difficult.
 *
 *  Created on: Aug 11, 2014
 *      Author: jdelgad
 */

#ifndef MOCK_WORKER_QUEUE_H_
#define MOCK_WORKER_QUEUE_H_


#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>

#include "worker_queue.h"

namespace solidfire
{

class MockWorkerQueue : public WorkerQueue
{
    public:
        explicit MockWorkerQueue(int number_of_threads)
          : WorkerQueue(number_of_threads) {
        }

        virtual ~MockWorkerQueue() {
        }

    private:
        MockWorkerQueue() = delete;
        MockWorkerQueue(const MockWorkerQueue&) = delete;
        MockWorkerQueue& operator=(const MockWorkerQueue&) = delete;
        MockWorkerQueue(const MockWorkerQueue&&) = delete;
        MockWorkerQueue& operator=(MockWorkerQueue &&) = delete;

        virtual void spawn() override {
            BOOST_LOG_TRIVIAL(trace) << "MockWorkerQueue::spawn()";
        }

        // this is the only task that actually does any work, by calling the
        // bound function passed in as an argument
        virtual void add_task(boost::function<void(void)> task) override {
            BOOST_LOG_TRIVIAL(trace) << "MockWorkerQueue::add_task()";
            task();
        }
        virtual void join_all() override {
            BOOST_LOG_TRIVIAL(trace) << "MockWorkerQueue::join_all()";
        }
        virtual void reset() override {
            BOOST_LOG_TRIVIAL(trace) << "MockWorkerQueue::reset()";
        }
        virtual void quit() override {
            BOOST_LOG_TRIVIAL(trace) << "MockWorkerQueue::quit()";
        }
};

}
#endif /* MOCK_WORKER_QUEUE_H_ */
