//
// Created by hasee on 2022/7/1.
//

#ifndef FLOWENGINE_VULKANVIEWPORT_H
#define FLOWENGINE_VULKANVIEWPORT_H

#include "Renderer/ViewPort.h"
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanFrameBuffer.h"

namespace Flow {

    struct VulkanViewPortSpec : public ViewPortSpec{
        VulkanFrameBufferSpecification spec;
    };

    class VulkanViewPort : public ViewPort {
    public:
        VulkanViewPort() = default;
        VulkanViewPort(UP(VulkanViewPortSpec) _spec);
        void init();
    private:
        VkViewport viewPort;
    };

} // Flow

#endif //FLOWENGINE_VULKANVIEWPORT_H
