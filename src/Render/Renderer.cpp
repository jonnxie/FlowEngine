//
// Created by hasee on 2022/6/29.
//

#include "Renderer.h"
#include "Platform/Vulkan/VulkanRenderer.h"

namespace Flow {

    std::shared_ptr<Renderer> Renderer::createRender() {
        #ifdef FLOW_GRAPHICS_VULKAN
            return std::make_shared<VulkanRenderer>();
        #endif
    }
} // FlowEnGine