//
// Created by hasee on 2022/7/23.
//

#include "VulkanRenderComponent.h"

#include <utility>
#include "VulkanRendererContext.h"
#include "VulkanRenderer.h"
#include "VulkanMaterial.h"
#include "VulkanPipeline.h"

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
        auto& sets = _mat->getSets();
        for (size_t i = 0; i < sets.size(); ++i) {
            bindMaterialSet(i, dynamic_cast<VulkanPipeline*>(_mat->getPipeline()),
                            static_cast<VulkanMaterialSet*>(sets[i].get()));
        }
    }

    void VulkanRenderComponent::bindMaterialSet(uint32_t _index, VulkanPipeline* _pipeline, VulkanMaterialSet* _set) {
        vkCmdBindDescriptorSets(cmb, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline->getLayout(), _index, 1, &_set->set, 0, nullptr);
    }
} // Flow