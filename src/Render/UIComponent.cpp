//
// Created by hasee on 2022/8/18.
//

#include "UIComponent.h"
#include "Platform/Vulkan/VulkanUIComponent.h"

namespace Flow {
    SP(UIComponent) UIComponent::createUIComponent() {
        #ifdef FLOW_GRAPHICS_VULKAN
            return std::shared_ptr<VulkanUIComponent>();
        #endif
    }
} // Flow