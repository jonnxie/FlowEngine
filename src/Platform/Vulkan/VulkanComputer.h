//
// Created by hasee on 2022/7/20.
//

#ifndef FLOWENGINE_VULKANCOMPUTER_H
#define FLOWENGINE_VULKANCOMPUTER_H

#include <vulkan/vulkan.h>
#include "Compute/Computer.h"
#include "Macro/Macro.h"
#include <vector>
#include <memory>

namespace Flow {

    class ThreadPool;

    class VulkanComputer final: public Computer{
    public:
        ~VulkanComputer() override;
    public:
        void compute(Scene* scene) override;
    private:
        void init();
        void createComputeCB();
        void createSemaphore();
        void createMultiThreadCMDPool();
    private:
        VkCommandBuffer computeCB{};
        VkSemaphore computeFinishedSemaphore{};
        std::vector<VkCommandPool> computeCMDPools;
    };

} // Flow

#endif //FLOWENGINE_VULKANCOMPUTER_H
