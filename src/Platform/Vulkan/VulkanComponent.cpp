//
// Created by hasee on 2022/7/27.
//

#include "VulkanComponent.h"
#include "VulkanRendererContext.h"
#include "VulkanRenderer.h"
#include "VulkanComputer.h"
#include "Render/Material.h"
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

    void VulkanComponent::bindMaterial(const Material *_mat, ComponentType _type) {
        auto& sets = _mat->getCSets();
        VulkanPipeline* pipeline = (VulkanPipeline *) (_mat->getPipeline());
        vkCmdBindPipeline(cmb, static_cast<VkPipelineBindPoint>(_type), pipeline->getPipeline());
        for (size_t i = 0; i < sets.size(); ++i) {
            bindMaterialSet(i, (VulkanPipeline *)(_mat->getPipeline()),
                            static_cast<VulkanMaterialSet*>(sets[i].get()), static_cast<VkPipelineBindPoint>(_type));
        }
    }

    void VulkanComponent::bindMaterialSet(uint32_t _index, VulkanPipeline *_pipeline, VulkanMaterialSet *_set, VkPipelineBindPoint _bindPoint) {
        vkCmdBindDescriptorSets(cmb, _bindPoint, _pipeline->getLayout(), _index, 1, &_set->set, 0, nullptr);
    }
} // Flow