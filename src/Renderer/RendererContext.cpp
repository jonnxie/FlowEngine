//
// Created by hasee on 2022/6/30.
//

#include "RendererContext.h"
#include "Platform/Vulkan/VulkanRendererContext.h"
#include "Platform/Vulkan/VulkanFrameBuffer.h"

namespace Flow {
    SP(RendererContext) RendererContext::get() {
#ifdef FLOW_GRAPHICS_VULKAN
        static SP(VulkanRendererContext) context = std::make_shared<VulkanRendererContext>();
        return context;
#endif
    }
} // Flow