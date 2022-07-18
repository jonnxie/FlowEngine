//
// Created by hasee on 2022/7/16.
//

#ifndef FLOWENGINE_VULKANMATERIAL_H
#define FLOWENGINE_VULKANMATERIAL_H

#include <vulkan/vulkan.h>
#include "Renderer/Material.h"
#include "VulkanSmartHandle.h"


namespace Flow {
    template<typename T>
    void generateVKResource(MaterialUnit& _unit, T& _vkResource)
    {

    }

    struct VulkanMaterialSet : MaterialSet{
        VulkanSmartHandle<VkDescriptorSet> set{VK_NULL_HANDLE};
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
        void bindFile(const std::string& _filename);
    };

    struct VulkanImageMaterialUnit : VulkanMaterialUnit{
        VulkanSmartHandle<VkImage> image{VK_NULL_HANDLE};
        VulkanSmartHandle<VkImageView> imageView{VK_NULL_HANDLE};
        VkImageUsageFlags imageUsageFlags;
        void bindFile(const std::string& _filename);
    };

} // Flow

#endif //FLOWENGINE_VULKANMATERIAL_H
