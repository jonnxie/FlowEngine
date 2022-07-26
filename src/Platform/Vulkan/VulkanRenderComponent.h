//
// Created by hasee on 2022/7/23.
//

#ifndef FLOWENGINE_VULKANRENDERCOMPONENT_H
#define FLOWENGINE_VULKANRENDERCOMPONENT_H

#include <vulkan/vulkan.h>
#include "Renderer/RenderComponent.h"

namespace Flow {

    class VulkanRenderComponent : public RenderComponent{
    public:
        explicit VulkanRenderComponent(std::function<void(RenderComponent*)> _renderFunction);
        ~VulkanRenderComponent() override;
    public:
        void bindThread(uint32_t _threadIndex);
        void drawIndex(size_t _count, size_t _offset) override;
    private:
        VkCommandBuffer cmb{};
    };

} // Flow

#endif //FLOWENGINE_VULKANRENDERCOMPONENT_H
