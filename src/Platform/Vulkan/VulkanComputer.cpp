//
// Created by hasee on 2022/7/20.
//

#include "VulkanComputer.h"
#include "VulkanMacro.h"
#include "VulkanRendererContext.h"
#include "Compute/threadpool.h"
#include "VulkanComputerComponent.h"
#include "Scene/Scene.h"
#include "Scene/Object.h"

namespace Flow {
    void VulkanComputer::compute(Scene *scene) {
        auto view = scene->GetAllObjectsWith<VulkanComputerComponent>();
        std::vector<VulkanComputerComponent*> components{};
        for (auto& entityID : view)
        {
            Object Object = { entityID, scene };
            components.push_back(&Object.getComponent<VulkanComputerComponent>());
        }
        threadPool->executeVector<VulkanComputerComponent*>(components, [](VulkanComputerComponent* _item,size_t _index, size_t _threadIndex){
            _item->bindThread(_threadIndex, ComponentType::Compute);
            (*_item)(_item);
        });
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
        VKExecute(vkCreateSemaphore(VulkanDevice, &semaphoreInfo, nullptr, &computeFinishedSemaphore))
    }

    void VulkanComputer::createMultiThreadCMDPool() {
        VkCommandPoolCreateInfo cmdPoolInfo = {};
        cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmdPoolInfo.pNext = VK_NULL_HANDLE;
        cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        cmdPoolInfo.queueFamilyIndex = VulkanContext->getIndices().computeFamily;
        for(auto& pool: computeCMDPools)
        {
            VKExecute(vkCreateCommandPool(VulkanDevice, &cmdPoolInfo, nullptr, &pool));
        }
    }

    void VulkanComputer::allocateCommandBuffer(uint32_t _threadIndex, VkCommandBuffer *_cmd) {
        VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.pNext = VK_NULL_HANDLE;
        commandBufferAllocateInfo.commandPool = computeCMDPools[_threadIndex];
        commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        commandBufferAllocateInfo.commandBufferCount = 1;

        VKExecute(vkAllocateCommandBuffers(VulkanDevice, &commandBufferAllocateInfo, _cmd));
    }
} // Flow