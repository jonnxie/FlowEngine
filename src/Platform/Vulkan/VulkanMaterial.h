//
// Created by hasee on 2022/7/16.
//

#ifndef FLOWENGINE_VULKANMATERIAL_H
#define FLOWENGINE_VULKANMATERIAL_H

#include <vulkan/vulkan.h>
#include "Renderer/Material.h"
#include "VulkanSmartHandle.h"
#include "VulkanTool.h"


namespace Flow {

    struct VulkanMaterialSet : MaterialSet{
        operator VkDescriptorSet() const {return set;};
        VkDescriptorSet set{VK_NULL_HANDLE};
    };

    struct VulkanMaterialUnit : MaterialUnit{
        VulkanSmartHandle<VkDeviceMemory> memory{VK_NULL_HANDLE};
        VkMemoryPropertyFlags memoryPropertyFlags;
        uint32_t binding;
        VulkanMaterialSet* set;
    };

    struct VulkanBufferMaterialUnit : VulkanMaterialUnit{
        VulkanSmartHandle<VkBuffer> buffer{VK_NULL_HANDLE};
        VkBufferUsageFlags bufferUsageFlags;

        template<class T>
        void bindFile(std::vector<T> _data, uint32_t _resourceType)
        {
            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;
            size_t bufferSize = _data.size() * sizeof(T);
            VkDevice device = VulkanDevice;
            tool::createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                               stagingBuffer,
                               stagingBufferMemory,
                               bufferSize);
            void *data;
            vkMapMemory(device,
                        stagingBufferMemory,
                        0,
                        bufferSize,
                        0,
                        &data);
            memset(data, 0, (size_t)bufferSize);
            memcpy(data,
                   _data.data(),
                   bufferSize);
            vkUnmapMemory(device, stagingBufferMemory);

            tool::createBuffer(bufferUsageFlags |
                         VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                         buffer,
                         memory,
                         bufferSize);

            tool::copyBuffer(stagingBuffer, buffer, bufferSize);

            vkDestroyBuffer(device, stagingBuffer, nullptr);
            vkFreeMemory(device, stagingBufferMemory, nullptr);
        };
    };

    enum class MaterialImageType{
        Dimension1 = 0,
        Dimension2,
        Dimension3,
    };

    struct VulkanImageMaterialUnit : VulkanMaterialUnit{
        VulkanSmartHandle<VkImage> image{VK_NULL_HANDLE};
        VulkanSmartHandle<VkImageView> imageView{VK_NULL_HANDLE};
        VkImageUsageFlags imageUsageFlags;
        void bindFile(const std::string& _filename, uint32_t _resourceType);
    };

} // Flow

#endif //FLOWENGINE_VULKANMATERIAL_H
