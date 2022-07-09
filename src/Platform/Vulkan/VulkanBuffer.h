//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANBUFFER_H
#define FLOWENGINE_VULKANBUFFER_H

#include "Macro/Macro.h"
#include "VulkanSmartHandle.h"
#include <vulkan/vulkan.h>

namespace Flow {

    class VulkanBuffer {
    public:
        VkBuffer getBuffer() const {return buffer;}
    private:
        VulkanSmartHandle<VkBuffer> buffer{VK_NULL_HANDLE};
        VulkanSmartHandle<VkDeviceMemory> memory{VK_NULL_HANDLE};
    };
} // Flow

#endif //FLOWENGINE_VULKANBUFFER_H
