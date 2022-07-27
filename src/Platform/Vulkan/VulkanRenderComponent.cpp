//
// Created by hasee on 2022/7/23.
//

#include "VulkanRenderComponent.h"

#include <utility>
#include "VulkanRendererContext.h"
#include "VulkanRenderer.h"

namespace Flow {
    VulkanRenderComponent::~VulkanRenderComponent() {
        auto pool = VulkanContext->getCBPool(CBType::Graphics);
        vkFreeCommandBuffers(VulkanDevice, pool, 1, &cmb);
    }

    void VulkanRenderComponent::drawIndex(size_t _count, size_t _offset) {
        vkCmdDrawIndexed(cmb, _count, 1, _offset, 0, 0);
    }

    VulkanRenderComponent::VulkanRenderComponent(std::function<void(RenderComponent*)> _renderFunction):
            RenderComponent(std::move(_renderFunction))
    {
    }

    void VulkanRenderComponent::bindMaterial(Material *_mat) {

    }
} // Flow