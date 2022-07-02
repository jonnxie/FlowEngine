//
// Created by hasee on 2022/7/1.
//

#include "ViewPort.h"
#include "Platform/Vulkan/VulkanViewPort.h"

namespace Flow{

    std::shared_ptr<ViewPort> ViewPort::createViewPort(UP(ViewPortSpec) _spec) {
#ifdef FLOW_GRAPHICS_VULKAN
        return std::make_shared<VulkanViewPort>(UP(VulkanViewPortSpec)((VulkanViewPortSpec*)_spec.get()));
#endif
    }

}
