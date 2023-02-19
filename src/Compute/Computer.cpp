//
// Created by hasee on 2022/7/20.
//

#include "Computer.h"
#include <memory>
#include "threadpool.h"
#include "MultiThreadComputer.h"
#include "Platform/Vulkan/VulkanComputer.h"

namespace Flow {
    void Computer::createThreadPool() {
        threadPool = std::make_unique<ThreadPool>();
    }

    SP(Computer) createMultipleComputer()
    {
        return std::make_shared<MultiThreadComputer>();
    }

    SP(Computer) createVulkanComputer()
    {
        return std::make_shared<VulkanComputer>();
    }

} // Flow