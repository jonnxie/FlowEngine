//
// Created by hasee on 2022/7/2.
//

#include "VulkanRenderer.h"
#include "VulkanRendererContext.h"

namespace Flow {
    void VulkanRenderer::init() {
        createCommandBuffer();
    }

    void VulkanRenderer::render(Scene *scene) {

    }

    void VulkanRenderer::attachFrameBuffer(FrameBuffer *frameBuffer) {

    }

    void VulkanRenderer::createCommandBuffer() {
        auto pool =  VulkanContext->getCBPool(CBType::Graphics);
        VkCommandBufferAllocateInfo allocateInfo {};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.pNext = VK_NULL_HANDLE;
        allocateInfo.commandPool = pool;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

        vkAllocateCommandBuffers(VulkanDevice, &allocateInfo, &graphicsCB);
    }

    VulkanRenderer::VulkanRenderer() {
        init();
    }

    VulkanRenderer::~VulkanRenderer() {
        auto pool =  VulkanContext->getCBPool(CBType::Graphics);
        vkFreeCommandBuffers(VulkanDevice, pool, 1, &graphicsCB);
    }
} // Flow