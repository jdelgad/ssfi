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
#include <boost/function.hpp>
#include <boost/thread.hpp>

class WorkerQueue
{
    public:
        explicit WorkerQueue(int number_of_threads);

        // use non-virtual idiom
        void spawn_threads();
        void add(boost::function<void(void)> task);
        void join();
        void clear();
        void stop();

        virtual ~WorkerQueue();

    protected:
        int get_number_of_threads() const;

    private:
        WorkerQueue() = delete;
        WorkerQueue(const WorkerQueue&) = delete;
        WorkerQueue& operator=(const WorkerQueue&) = delete;
        WorkerQueue(const WorkerQueue&&) = delete;
        WorkerQueue& operator=(WorkerQueue &&) = delete;

        virtual void spawn() = 0;
        virtual void add_task(boost::function<void(void)> task) = 0;
        virtual void join_all() = 0;
        virtual void reset() = 0;
        virtual void quit() = 0;

        int m_num_threads;
};

#endif /* WORKER_H_ */
