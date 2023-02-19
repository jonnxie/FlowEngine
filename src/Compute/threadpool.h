//
// Created by AnWell on 2021/8/16.
//

#ifndef SHATTER_ENGINE_THREADPOOL_H
#define SHATTER_ENGINE_THREADPOOL_H

#include <thread>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <future>
#include <type_traits>
#include <condition_variable>
#include "Macro/Macro.h"
#include "Computer.h"


namespace Flow
{
    class Thread
    {
    public:
        Thread();
        ~Thread();
    public:
        void wait();
        void work();
        void addTask(std::function<void()> _task);
    public:
        std::thread m_work;
        bool m_destroyed = false;
        std::mutex m_task_mutex;
        std::condition_variable m_condition;
        std::queue<std::function<void()>> m_tasks;
    };

    class ThreadPool
    {
    private:
        void setThreadCount(uint32_t count = std::thread::hardware_concurrency())
        {
            m_thread_count = count;
            threads.clear();
            for(auto i = 0; i < count; i++)
            {
                threads.emplace_back(new Thread);
            }
        }
    public:
        void addTask(const std::function<void()>& _task);

        void addTasks(const std::array<std::function<void()>,4>& _array);


        void wait()
        {
            for(auto &thread : threads)
            {
                thread->wait();
            }
        }

        Thread* operator[](size_t _index){
            return threads[_index];
        }

        using IndexPair = std::pair<size_t, size_t>;

        void allocateExecuteArray(size_t _taskCount, std::vector<IndexPair>& _array);

        template<class Item>
        void executeVector(std::vector<Item>& _vec, std::function<void(Item&,size_t, size_t)> _task)
        {
            size_t taskCount = _vec.size();
            std::vector<IndexPair> indexPairs;
            allocateExecuteArray(taskCount, indexPairs);
            for (size_t i = 0; i < m_thread_count; ++i) {
                addTask([&, i](){
                    for (int j = 0; j < indexPairs[i].second; ++j)
                    {
                        size_t index = j + indexPairs[i].first;
                        _task(_vec[index], index, i);
                    }
                });
            }
        }

    public:
        uint32_t m_index = 0;
        std::vector<Thread*> threads;
        uint32_t m_thread_count;
    public:
        explicit ThreadPool(uint32_t count);
        ThreadPool();
        ~ThreadPool();
        DisableCopy(ThreadPool);
    };
}
#define SingleThreadPool ThreadPool::pool()

#endif //SHATTER_ENGINE_THREADPOOL_H
