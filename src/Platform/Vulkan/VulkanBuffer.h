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
        VulkanBuffer() = default;
        ~VulkanBuffer();
        VulkanBuffer(VkBufferUsageFlags _flags, VkMemoryPropertyFlags _property, uint64_t _size);
        VulkanBuffer& operator=(const VulkanBuffer& _buffer)
        {
            this->buffer = VkBuffer(_buffer.buffer);
            this->memory = VkDeviceMemory(_buffer.memory);
            this->mapped = _buffer.mapped;
            return *this;
        }
    public:
        VkBuffer getBuffer() const {return buffer;}
        explicit operator void*() const {return mapped;}
        void map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
        void unmap();
    private:
        VulkanSmartHandle<VkBuffer> buffer{VK_NULL_HANDLE};
        VulkanSmartHandle<VkDeviceMemory> memory{VK_NULL_HANDLE};
        void* mapped{nullptr};

    };
} // Flow

#endif //FLOWENGINE_VULKANBUFFER_H
