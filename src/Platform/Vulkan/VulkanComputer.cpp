//
// Created by hasee on 2022/7/20.
//

#include "VulkanComputer.h"
#include "VulkanRendererContext.h"

namespace Flow {
    void VulkanComputer::compute(Scene *scene) {

    }

    VulkanComputer::~VulkanComputer() {
        auto pool = VulkanContext->getCBPool(CBType::Compute);
        vkFreeCommandBuffers(VulkanDevice, pool, 1, &computeCB);
    }

    void VulkanComputer::init() {
        createComputeCB();
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
} // Flow