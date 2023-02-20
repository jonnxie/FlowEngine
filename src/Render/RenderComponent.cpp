//
// Created by hasee on 2022/7/23.
//

#include "RenderComponent.h"
#include "Platform/Vulkan/VulkanRenderComponent.h"

namespace Flow {
    SP(RenderComponent) RenderComponent::createRenderComponent(const std::function<void(RenderComponent*)>& _renderFunction) {
        #ifdef FLOW_GRAPHICS_VULKAN
        return std::make_shared<VulkanRenderComponent>(_renderFunction);
        #endif
    }

    Renderer *RenderComponent::getRenderer() {
        return renderer;
    }

    void RenderComponent::setRenderer(Renderer* _renderer) {
        renderer = _renderer;
    }

    RenderComponentMiddle::RenderComponentMiddle(std::function<void(RenderComponent*)> _renderFunction) {
        #ifdef FLOW_GRAPHICS_VULKAN
            renderComponent = std::make_shared<VulkanRenderComponent>(std::move(_renderFunction));
        #endif
    }
} // Flow