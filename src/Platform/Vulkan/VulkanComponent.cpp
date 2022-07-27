//
// Created by hasee on 2022/7/27.
//

#include "VulkanComponent.h"
#include "VulkanRendererContext.h"
#include "VulkanRenderer.h"
#include "VulkanComputer.h"


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
} // Flow