//
// Created by hasee on 2022/7/27.
//

#include "VulkanComponent.h"
#include "VulkanRendererContext.h"
#include "VulkanRenderer.h"
#include "VulkanComputer.h"
#include "Renderer/Material.h"
#include "VulkanPipeline.h"
#include "VulkanMaterial.h"

namespace Flow {
    void VulkanComponent::bindThread(uint32_t _threadIndex, ComponentType _type) {
        switch (_type) {
            case ComponentType::Render:
            {
                auto renderer = VulkanContext->getRenderer();
                return renderer->allocateCommandBuffer(_threadIndex, &cmb);
            }
            case ComponentType::Compute:
            {
                auto computer = VulkanContext->getRenderer();
                return computer->allocateCommandBuffer(_threadIndex, &cmb);
            }
        }
    }

    void VulkanComponent::bindMaterial(Material *_mat, ComponentType _type) {
        auto& sets = _mat->getSets();
        VulkanPipeline* pipeline = dynamic_cast<VulkanPipeline *>(_mat->getPipeline());
        VkPipelineBindPoint bindPoint = _type == ComponentType::Compute ? VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
        vkCmdBindPipeline(cmb, bindPoint, pipeline->getPipeline());
        for (size_t i = 0; i < sets.size(); ++i) {
            bindMaterialSet(i, dynamic_cast<VulkanPipeline*>(_mat->getPipeline()),
                            static_cast<VulkanMaterialSet*>(sets[i].get()), bindPoint);
        }
    }

    void VulkanComponent::bindMaterialSet(uint32_t _index, VulkanPipeline *_pipeline, VulkanMaterialSet *_set, VkPipelineBindPoint _bindPoint) {
        vkCmdBindDescriptorSets(cmb, _bindPoint, _pipeline->getLayout(), _index, 1, &_set->set, 0, nullptr);
    }
} // Flow