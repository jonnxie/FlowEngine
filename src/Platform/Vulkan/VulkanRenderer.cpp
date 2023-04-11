//
// Created by hasee on 2022/7/2.
//

#include "VulkanRenderer.h"
#include "VulkanMacro.h"
#include "VulkanRendererContext.h"
#include "Scene/Scene.h"
#include <thread>
#include "Compute/threadpool.h"
#include "VulkanRenderComponent.h"
#include "VulkanFrameBuffer.h"
#include "Scene/Object.h"
#include "Scene/Camera.h"

namespace Flow {
    void VulkanRenderer::init() {
        context = VulkanContext;
        createCommandBuffer();
        createSemaphore();
        createThreadPool();
        createMultiThreadCMDPool();
    }

    void VulkanRenderer::render(Scene *scene) {
        auto view = scene->GetAllObjectsWith<RenderComponentMiddle>();
        std::vector<VulkanRenderComponent*> components{};
        for (auto& entityID : view)
        {
            Object Object = { entityID, scene };
            auto ptr = dynamic_cast<VulkanRenderComponent*>(Object.getComponent<RenderComponentMiddle>()());
            ptr->setRenderer(this);
            components.push_back(ptr);
        }
        /*
         * Bind Multi Viewport
         */
        const auto& viewports = scene->getViewPorts();
        for (auto& [id, viewport] : viewports)
        {
            VulkanFrameBuffer* fb = dynamic_cast<VulkanFrameBuffer *>(viewport->getFrameBuffer().get());
            renderBegin(fb);
            threadPool->executeVector<VulkanRenderComponent*>(components, [this](VulkanRenderComponent* _item,size_t _index, size_t _threadIndex){
                _item->bindThread(_threadIndex);
                _item->setCMBBeginInfo(&commandBufferBeginInfo);
                (*_item)(_item);
            });
            threadPool->wait();
            renderEnd(fb);
            cmbVec.push_back(fb->getCMD());
        }
    }

    void VulkanRenderer::attachFrameBuffer(FrameBuffer *frameBuffer) {

    }

    void VulkanRenderer::createCommandBuffer() {
//        auto pool =  context->getCBPool(CBType::Graphics);
//        VkCommandBufferAllocateInfo allocateInfo {};
//        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//        allocateInfo.pNext = VK_NULL_HANDLE;
//        allocateInfo.commandPool = pool;
//        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//
//        VKExecute(vkAllocateCommandBuffers(*context, &allocateInfo, &graphicsCB))
    }

    VulkanRenderer::VulkanRenderer() {
        init();
    }

    VulkanRenderer::~VulkanRenderer() {
//        auto pool =  VulkanContext->getCBPool(CBType::Graphics);
//        vkFreeCommandBuffers(VulkanDevice, pool, 1, &graphicsCB);
    }

    void VulkanRenderer::createSemaphore() {
        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VKExecute(vkCreateSemaphore(VulkanDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore))
    }

    void VulkanRenderer::createMultiThreadCMDPool() {
        VkCommandPoolCreateInfo cmdPoolInfo = {};
        cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmdPoolInfo.pNext = VK_NULL_HANDLE;
        cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        cmdPoolInfo.queueFamilyIndex = VulkanContext->getIndices().graphicsFamily;
        graphicsCMDPools.resize(threadPool->m_thread_count);
        for(auto& pool: graphicsCMDPools)
        {
            VKExecute(vkCreateCommandPool(VulkanDevice, &cmdPoolInfo, nullptr, &pool))
        }
    }

    void VulkanRenderer::createThreadPool() {
        threadPool = std::make_unique<ThreadPool>();
    }

    void VulkanRenderer::allocateCommandBuffer(uint32_t _threadIndex, VkCommandBuffer* _cmd) {
        VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.pNext = VK_NULL_HANDLE;
        commandBufferAllocateInfo.commandPool = graphicsCMDPools[_threadIndex];
        commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        commandBufferAllocateInfo.commandBufferCount = 1;

        VKExecute(vkAllocateCommandBuffers(VulkanDevice, &commandBufferAllocateInfo, _cmd));
    }

    void VulkanRenderer::bindCamera(Camera* _camera) {

    }

    void VulkanRenderer::renderBegin(VulkanFrameBuffer* frameBuffer) {
        VkCommandBufferBeginInfo cmdBufInfo{};
        {
            cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            cmdBufInfo.pNext = VK_NULL_HANDLE;
            cmdBufInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
            cmdBufInfo.pInheritanceInfo = VK_NULL_HANDLE;
        }

        VkRenderPassBeginInfo renderPassBeginInfo{};
        {
            auto spec = frameBuffer->getSpec();
            renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassBeginInfo.pNext = VK_NULL_HANDLE;
            renderPassBeginInfo.renderPass = frameBuffer->getRenderPass();
            renderPassBeginInfo.framebuffer = frameBuffer->getFrameBuffer();
            renderPassBeginInfo.renderArea.offset = {0, 0};
            renderPassBeginInfo.renderArea.extent = VkExtent2D {spec->Width, spec->Height};
            renderPassBeginInfo.clearValueCount = spec->formats.size();
            std::vector<VkClearValue> values{};
            VkClearValue clearValue;
            for (auto& format : spec->formats)
            {
                if (format.usage == Usage::Color)
                {
                    memcpy(clearValue.color.int32, format.clearValue.color.int32, one_float4);
                    values.push_back(clearValue);
                } else
                {
                    memcpy(&clearValue.depthStencil, &format.clearValue.depthStencil, one_vec2);
                    values.push_back(clearValue);
                }
            }
            renderPassBeginInfo.pClearValues = values.data();
            vkCmdBeginRenderPass(frameBuffer->getCMD(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
            inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
            inheritanceInfo.pNext = VK_NULL_HANDLE;
            inheritanceInfo.renderPass = frameBuffer->getRenderPass();
            inheritanceInfo.subpass = 0;
            inheritanceInfo.framebuffer = frameBuffer->getFrameBuffer();
            inheritanceInfo.occlusionQueryEnable = false;

            commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            commandBufferBeginInfo.pNext = VK_NULL_HANDLE;
            commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
            commandBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;
        }
    }

    void VulkanRenderer::renderEnd(VulkanFrameBuffer* frameBuffer) {
        vkCmdEndRenderPass(frameBuffer->getCMD());
        vkEndCommandBuffer(frameBuffer->getCMD());
    }
} // Flow