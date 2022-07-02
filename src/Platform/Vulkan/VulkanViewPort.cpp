//
// Created by hasee on 2022/7/1.
//

#include "VulkanViewPort.h"

namespace Flow {
    VulkanViewPort::VulkanViewPort(UP(VulkanViewPortSpec) _spec) : ViewPort(
    std::move(_spec)) {
        init();
    }

    void VulkanViewPort::init() {

    }
} // Flow