//
// Created by hasee on 2022/7/7.
//

#include "UI.h"
#include "Platform/Vulkan/VulkanUI.h"
#include "Window/window.h"

namespace Flow {
    SP(UI) UI::createUI(Window *_window) {
        #ifdef FLOW_GRAPHICS_VULKAN
        return std::make_shared<VulkanUI>(_window);
        #endif
    }
} // Flow