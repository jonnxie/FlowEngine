//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_VULKANRENDERER_H
#define FLOWENGINE_VULKANRENDERER_H

#include "Renderer/Renderer.h"
#include <vulkan/vulkan.h>
#include "VulkanSmartHandle.h"

namespace Flow {

    class VulkanRendererContext;

    class VulkanRenderer : public Renderer{
    public:
        VulkanRenderer();
        ~VulkanRenderer();
        DisableCopy(VulkanRenderer);
    public:
        void render(Scene* scene) override;
        void attachFrameBuffer(FrameBuffer* frameBuffer) override;
    private:
        void init();
        void createCommandBuffer();
    private:
        VulkanRendererContext* context;
        VkCommandBuffer graphicsCB;
    };

} // Flow

#endif //FLOWENGINE_VULKANRENDERER_H
