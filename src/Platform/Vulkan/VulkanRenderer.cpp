//
// Created by hasee on 2022/7/2.
//

#include "VulkanRenderer.h"
#include "VulkanRendererContext.h"
#include "Scene/Scene.h"
#include <thread>
#include "Compute/threadpool.h"
#include "VulkanRenderComponent.h"
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
        auto view = scene->GetAllObjectsWith<VulkanRenderComponent>();
        std::vector<VulkanRenderComponent*> components{};
        for (auto& entityID : view)
        {
            Object Object = { entityID, scene };
            auto ptr = &Object.getComponent<VulkanRenderComponent>();
            ptr->setRenderer(this);
            components.push_back(ptr);
        }
        threadPool->executeVector<VulkanRenderComponent*>(components, [](VulkanRenderComponent* _item,size_t _index, size_t _threadIndex){
            _item->bindThread(_threadIndex);
            (*_item)(_item);
        });
    }

    void VulkanRenderer::attachFrameBuffer(FrameBuffer *frameBuffer) {

    }

    void VulkanRenderer::createCommandBuffer() {
        auto pool =  context->getCBPool(CBType::Graphics);
        VkCommandBufferAllocateInfo allocateInfo {};
        allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocateInfo.pNext = VK_NULL_HANDLE;
        allocateInfo.commandPool = pool;
        allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

#ifdef NDEBUG
        vkAllocateCommandBuffers(*context, &allocateInfo, &graphicsCB);
#else
        VK_CHECK_RESULT(vkAllocateCommandBuffers(*context, &allocateInfo, &graphicsCB));
#endif
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
#ifdef NDEBUG
        vkCreateSemaphore(VulkanDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore);
#else
        VK_CHECK_RESULT(vkCreateSemaphore(VulkanDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore));
#endif
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
            #ifdef NDEBUG
            vkCreateCommandPool(VulkanDevice, &cmdPoolInfo, nullptr, &pool);
            #else
            VK_CHECK_RESULT(vkCreateCommandPool(VulkanDevice, &cmdPoolInfo, nullptr, &pool));
            #endif
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

        #ifdef NDEBUG
        vkAllocateCommandBuffers(VulkanDevice, &commandBufferAllocateInfo, _cmd);
        #else
        VK_CHECK_RESULT(vkAllocateCommandBuffers(VulkanDevice, &commandBufferAllocateInfo, _cmd));
        #endif
    }

    void VulkanRenderer::bindCamera(Camera* _camera) {

    }
} // Flow