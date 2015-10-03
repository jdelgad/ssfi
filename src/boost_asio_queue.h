/*
 * boost_asio_queue.h
 *
 *  Created on: Aug 11, 2014
 *      Author: Jacob Delgado
 */

#ifndef BOOST_ASIO_QUEUE_H_
#define BOOST_ASIO_QUEUE_H_

#include "worker_queue.h"

#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace ssfi
{

class BoostAsIOQueue : public WorkerQueue
{
    public:
        explicit BoostAsIOQueue(int number_of_threads);

        virtual ~BoostAsIOQueue();

    private:
        BoostAsIOQueue() = delete;
        BoostAsIOQueue(const BoostAsIOQueue&) = delete;
        BoostAsIOQueue& operator=(const BoostAsIOQueue&) = delete;
        BoostAsIOQueue(const BoostAsIOQueue&&) = delete;
        BoostAsIOQueue& operator=(BoostAsIOQueue &&) = delete;

        virtual void spawn() override;
        virtual void add_task(boost::function<void(void)> task) override;
        virtual void join_all() override;
        virtual void reset() override;
        virtual void quit() override;

        // NOTE: ordering matters, work must be done after io_service, but
        // before thread_group
        boost::asio::io_service m_io_service;
        std::shared_ptr<boost::asio::io_service::work> m_work_ptr;
        boost::thread_group m_threads;
};

}

#endif /* BOOST_ASIO_QUEUE_H_ */
