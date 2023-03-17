//
// Created by hasee on 2022/7/23.
//

#include "RenderComponent.h"

#include <utility>
#include "Platform/Vulkan/VulkanRenderComponent.h"

namespace Flow {
    UP(RenderComponent) RenderComponent::createRenderComponent(std::function<void(RenderComponent*)> _renderFunction) {
        #ifdef FLOW_GRAPHICS_VULKAN
        return std::make_unique<VulkanRenderComponent>(std::move(_renderFunction));
        #endif
    }

    Renderer *RenderComponent::getRenderer() {
        return renderer;
    }

    void RenderComponent::setRenderer(Renderer* _renderer) {
        renderer = _renderer;
    }

    SP(Material) RenderComponent::getMaterial() {
        return material;
    }

    void RenderComponent::setMaterial(SP(Material)_material) {
        material = std::move(_material);
    }

    RenderComponentMiddle::RenderComponentMiddle(std::function<void(RenderComponent*)> _renderFunction):
            renderFunction(std::move(_renderFunction)){
        #ifdef FLOW_GRAPHICS_VULKAN
            renderComponent = RenderComponent::createRenderComponent(std::move(_renderFunction));
        #endif
    }

    RenderComponentMiddle::RenderComponentMiddle(const RenderComponentMiddle &_middle) {
        renderFunction = _middle.renderFunction;
#ifdef FLOW_GRAPHICS_VULKAN
        renderComponent = RenderComponent::createRenderComponent(std::move(renderFunction));
#endif
    }

    RenderComponentMiddle &RenderComponentMiddle::operator=(const RenderComponentMiddle &_middle) {
        renderFunction = _middle.renderFunction;
        #ifdef FLOW_GRAPHICS_VULKAN
                renderComponent = RenderComponent::createRenderComponent(std::move(renderFunction));
        #endif
        return *this;
    }

    RenderComponentMiddle &RenderComponentMiddle::operator=(RenderComponentMiddle &&_middle) {
        renderFunction = _middle.renderFunction;
#ifdef FLOW_GRAPHICS_VULKAN
        renderComponent = RenderComponent::createRenderComponent(std::move(renderFunction));
#endif
        return *this;
    }

    RenderComponentMiddle::RenderComponentMiddle(RenderComponentMiddle &&_middle) noexcept {
        renderFunction = _middle.renderFunction;
#ifdef FLOW_GRAPHICS_VULKAN
        renderComponent = RenderComponent::createRenderComponent(std::move(renderFunction));
#endif
    }
} // Flow