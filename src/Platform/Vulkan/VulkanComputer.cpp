//
// Created by hasee on 2022/7/20.
//

#include "VulkanComputer.h"
#include "VulkanRendererContext.h"
#include "Compute/threadpool.h"

namespace Flow {
    void VulkanComputer::compute(Scene *scene) {

    }

    VulkanComputer::~VulkanComputer() {
        auto pool = VulkanContext->getCBPool(CBType::Compute);
        vkFreeCommandBuffers(VulkanDevice, pool, 1, &computeCB);
    }

    void VulkanComputer::init() {
        createComputeCB();
        createSemaphore();
        createThreadPool();
        createMultiThreadCMDPool();
    }

    void VulkanComputer::createComputeCB() {
        auto pool = VulkanContext->getCBPool(CBType::Compute);
        VkCommandBufferAllocateInfo allocateInfo {};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.pNext = VK_NULL_HANDLE;
        allocateInfo.commandPool = pool;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

        vkAllocateCommandBuffers(VulkanDevice, &allocateInfo, &computeCB);
    }

    void VulkanComputer::createSemaphore() {
        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
#ifdef NDEBUG
        vkCreateSemaphore(VulkanDevice, &semaphoreInfo, nullptr, &computeFinishedSemaphore);
#else
        if (vkCreateSemaphore(VulkanDevice, &semaphoreInfo, nullptr, &computeFinishedSemaphore) != VK_SUCCESS) {
            FlowError(failed to create semaphores!);
        }
#endif
    }

    void VulkanComputer::createMultiThreadCMDPool() {
        VkCommandPoolCreateInfo cmdPoolInfo = {};
        cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmdPoolInfo.pNext = VK_NULL_HANDLE;
        cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        cmdPoolInfo.queueFamilyIndex = VulkanContext->getIndices().computeFamily;
        for(auto& pool: computeCMDPools)
        {
#ifdef NDEBUG
            vkCreateCommandPool(VulkanDevice, &cmdPoolInfo, nullptr, &pool);
#else
            VK_CHECK_RESULT(vkCreateCommandPool(VulkanDevice, &cmdPoolInfo, nullptr, &pool));
#endif
        }
    }

    void VulkanComputer::createThreadPool() {
        threadPool = std::make_unique<ThreadPool>();
    }
} // Flow