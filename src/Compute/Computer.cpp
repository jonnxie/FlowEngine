//
// Created by hasee on 2022/7/20.
//

#include "Computer.h"
#include <memory>
#include "threadpool.h"

namespace Flow {
    void Computer::createThreadPool() {
        threadPool = std::make_unique<ThreadPool>();
    }
} // Flow