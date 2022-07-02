//
// Created by hasee on 2022/6/29.
//

#include "FrameBuffer.h"
#include "Platform/Vulkan/VulkanFrameBuffer.h"

namespace Flow{
    SP(FrameBuffer) Flow::FrameBuffer::createFramebuffer(std::unique_ptr<FrameBufferSpecification> _spec) {
#ifdef FLOW_GRAPHICS_VULKAN
        return std::make_shared<VulkanFrameBuffer>(UP(VulkanFrameBufferSpecification)((VulkanFrameBufferSpecification*)_spec.get()));
#endif
    }
}

