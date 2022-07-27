//
// Created by hasee on 2022/7/27.
//

#include "VulkanComputerComponent.h"

namespace Flow {
    void VulkanComputerComponent::bindMaterial(Material *_mat) {

    }

    VulkanComputerComponent::VulkanComputerComponent(std::function<void(ComputerComponent *)> _renderFunction)
            : ComputerComponent(_renderFunction) {

    }

    VulkanComputerComponent::~VulkanComputerComponent() {

    }
} // Flow