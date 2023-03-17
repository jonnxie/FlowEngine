//
// Created by hasee on 2022/6/30.
//

#include "VulkanBuffer.h"
#include "VulkanRendererContext.h"
#include "VulkanTool.h"
#include "VulkanMacro.h"

namespace Flow {
    VulkanBuffer::VulkanBuffer(VkBufferUsageFlags _flags, VkMemoryPropertyFlags _property, uint64_t _size) {
        tool::createBuffer(_flags, _property, buffer, memory, _size);
    }

    VulkanBuffer::~VulkanBuffer() {
        unmap();
    }

    void VulkanBuffer::unmap() {
        if (mapped)
        {
            vkUnmapMemory(VulkanDevice, memory);
            mapped = nullptr;
        }
    }

    void VulkanBuffer::map(VkDeviceSize size, VkDeviceSize offset) {
        if (!mapped)
        {
            VKExecute(vkMapMemory(VulkanDevice, memory, offset, size, 0, &mapped));
        }
    }
} // Flow