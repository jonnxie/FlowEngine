//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_VULKANRENDERER_H
#define FLOWENGINE_VULKANRENDERER_H

#include "Render/Renderer.h"
#include <vulkan/vulkan.h>
#include "VulkanSmartHandle.h"

namespace Flow {

    class VulkanRendererContext;

    class ThreadPool;

    class Camera;

    class VulkanFrameBuffer;

    class VulkanRenderer final : public Renderer {
    public:
        VulkanRenderer();
        ~VulkanRenderer() override;
        DisableCopy(VulkanRenderer);
    public:
        void render(Scene* scene) override;
        void attachFrameBuffer(FrameBuffer* frameBuffer) override;
        void allocateCommandBuffer(uint32_t _threadIndex, VkCommandBuffer* _cmd);
    private:
        void init();
        void renderBegin(VulkanFrameBuffer* frameBuffer);
        void renderEnd(VulkanFrameBuffer* frameBuffer);
        void createCommandBuffer();
        void createSemaphore();
        void createThreadPool();
        void createMultiThreadCMDPool();
        void bindCamera(Camera* _camera);
    private:
        VulkanRendererContext* context;
        VkCommandBuffer graphicsCB;
        VkSemaphore renderFinishedSemaphore;
        std::vector<VkCommandPool> graphicsCMDPools;
        UP(ThreadPool) threadPool;
    };

} // Flow

#endif //FLOWENGINE_VULKANRENDERER_H
