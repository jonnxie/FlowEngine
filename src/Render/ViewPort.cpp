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

    UP(ViewPortSpec) makeViewPortSpec(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height,
                                      const Camera &_camera) {
        auto ptr = std::make_unique<ViewPortSpec>();
        ptr->x = _x;
        ptr->y = _y;
        ptr->width = _width;
        ptr->height = _height;
        ptr->camera = _camera;
        return ptr;
    }
}
