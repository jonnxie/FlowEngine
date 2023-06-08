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
//        bindCamera()
        threadPool->executeVector<VulkanRenderComponent*>(components, [](VulkanRenderComponent* _item,size_t _index, size_t _threadIndex){
            _item->bindThread(_threadIndex);
            (*_item)(_item);
        });
    }

    void VulkanRenderer::attachFrameBuffer(FrameBuffer *frameBuffer) {
        auto fbo(dynamic_cast<VulkanFrameBuffer*>(frameBuffer));

    }

    void VulkanRenderer::createCommandBuffer() {
        auto pool =  context->getCBPool(CBType::Graphics);
        VkCommandBufferAllocateInfo allocateInfo {};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.pNext = VK_NULL_HANDLE;
        allocateInfo.commandPool = pool;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

        VKExecute(vkAllocateCommandBuffers(*context, &allocateInfo, &graphicsCB))
    }

    VulkanRenderer::VulkanRenderer() {
        init();
    }

    VulkanRenderer::~VulkanRenderer() {
        auto pool =  VulkanContext->getCBPool(CBType::Graphics);
        vkFreeCommandBuffers(VulkanDevice, pool, 1, &graphicsCB);
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
} // Flow