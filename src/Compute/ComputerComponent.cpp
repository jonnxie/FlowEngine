//
// Created by hasee on 2022/7/27.
//

#include "ComputerComponent.h"
#include "Platform/Vulkan/VulkanComputerComponent.h"

namespace Flow {
    SP(ComputerComponent) ComputerComponent::createComputerComponent() {
        #ifdef FLOW_GRAPHICS_VULKAN
        return std::shared_ptr<VulkanComputerComponent>();
        #endif
    }
} // Flow