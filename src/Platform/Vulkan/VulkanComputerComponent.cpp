//
// Created by hasee on 2022/7/27.
//

#include "VulkanComputerComponent.h"

#include <utility>
#include "VulkanPipeline.h"
#include "VulkanMaterial.h"

namespace Flow {
    void VulkanComputerComponent::bindMaterial(Material *_mat) {
        VulkanComponent::bindMaterial(_mat, ComponentType::Compute);
    }

    VulkanComputerComponent::VulkanComputerComponent(std::function<void(ComputerComponent *)> _computeFunction)
            : ComputerComponent(std::move(_computeFunction)) {

    }

    VulkanComputerComponent::~VulkanComputerComponent()
    {

    }

    void VulkanComputerComponent::dispatch(uint32_t _xCount, uint32_t _yCount, uint32_t _zCount) {
        vkCmdDispatch(cmb, _xCount, _yCount, _zCount);
    }
} // Flow