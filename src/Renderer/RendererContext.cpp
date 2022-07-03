//
// Created by hasee on 2022/6/30.
//

#include "RendererContext.h"
#include "Platform/Vulkan/VulkanRendererContext.h"
#include "Platform/Vulkan/VulkanFrameBuffer.h"

namespace Flow {

    SP(RendererContext)RendererContext::context = nullptr;

    void RendererContext::createRenderContext(Window* _window) {
#ifdef FLOW_GRAPHICS_VULKAN
        context = std::make_shared<VulkanRendererContext>(_window);
#endif
    }

    SP(RendererContext) RendererContext::get() {
        return context;
    }
} // Flow