//
// Created by AnWell on 2021/8/16.
//
#include "threadpool.h"

namespace Flow {

    Thread::Thread() {
        m_work = std::thread(&Thread::work,this);
    }

    Thread::~Thread() {
        if(m_work.joinable())
        {
            wait();
            m_task_mutex.lock();
            m_destroyed = true;
            m_condition.notify_one();
            m_task_mutex.unlock();
            m_work.join();
        }
    }

    void Thread::work() {
        std::function<void()> tmp_jobs;
        while(true){
            {
                std::unique_lock<std::mutex> uniqueLock(m_task_mutex);
                m_condition.wait(uniqueLock,[this](){return
                        !m_tasks.empty() || m_destroyed;});
                if(m_destroyed)
                {
                    break;
                }
                tmp_jobs = m_tasks.front();
            }
            tmp_jobs();
            {
                std::lock_guard<std::mutex> lock(m_task_mutex);
                m_tasks.pop();
                m_condition.notify_one();
            }
        }
    }

    void Thread::addTask(std::function<void()> _task) {
        std::lock_guard<std::mutex> guard_lock(m_task_mutex);

        m_tasks.push(std::move(_task));
        m_condition.notify_one();

    }

    void Thread::wait() {
        std::unique_lock<std::mutex> uniqueLock(m_task_mutex);
        m_condition.wait(uniqueLock, [this](){return m_tasks.empty();});
    }

    ThreadPool::ThreadPool(uint32_t count) {
        setThreadCount(count);
    }

    ThreadPool::ThreadPool() {
        setThreadCount();
    }

    ThreadPool::~ThreadPool() {
        for(auto& thread: threads)
        {
            delete thread;
        }
    }

    void ThreadPool::addTask(const std::function<void()> &_task) {
        threads[m_index++]->addTask(_task);
        if(m_index >= m_thread_count){
            m_index -= m_thread_count;
        }
    }

    void ThreadPool::addTasks(const std::array<std::function<void()>,4>& _array){
        for(size_t index = 0; index < 4; index++)
        {
            threads[m_index++]->addTask(_array[index]);
            if(m_index >= m_thread_count){
                m_index -= m_thread_count;
            }
        }
    }

    void ThreadPool::allocateExecuteArray(size_t _taskCount, std::vector<IndexPair>& _array) {
        _array.resize(m_thread_count);
        size_t baseCount = _taskCount / m_thread_count;
        size_t leftCount = _taskCount % m_thread_count;
        size_t offset = 0;
        for (int i = 0; i < m_thread_count; ++i) {
            if (i < leftCount)
            {
                _array[i] = IndexPair(offset, baseCount + 1);
                offset += baseCount + 1;
            } else {
                _array[i] = IndexPair(offset, baseCount);
                offset += baseCount;
            }
        }
    }
}

