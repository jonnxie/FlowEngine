//
// Created by hasee on 2022/7/16.
//

#ifndef FLOWENGINE_VULKANMATERIAL_H
#define FLOWENGINE_VULKANMATERIAL_H

#include <vulkan/vulkan.h>
#include "Render/Material.h"
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

        void bindData(void* _data, size_t _size)
        {
            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;
            VkDevice device = VulkanDevice;
            tool::createBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                               VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                               stagingBuffer,
                               stagingBufferMemory,
                               _size);
            void *data;
            vkMapMemory(device,
                        stagingBufferMemory,
                        0,
                        _size,
                        0,
                        &data);
            memset(data, 0, (size_t)_size);
            memcpy(data,
                   _data,
                   _size);
            vkUnmapMemory(device, stagingBufferMemory);

            tool::createBuffer(bufferUsageFlags |
                               VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                               VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                               buffer,
                               memory,
                               _size);

            tool::copyBuffer(stagingBuffer, buffer, _size);

            vkDestroyBuffer(device, stagingBuffer, nullptr);
            vkFreeMemory(device, stagingBufferMemory, nullptr);

            VkDescriptorBufferInfo bufferInfo{
                    buffer,
                    0,
                    _size
            };
            VkWriteDescriptorSet writeSet = tool::writeDescriptorSet(this->set->set,
                                                                     tool::reflectBufferDescriptorType(bufferUsageFlags),
                                                                     binding,
                                                                     &bufferInfo);
            vkUpdateDescriptorSets(device,
                                   1,
                                   &writeSet,
                                   0,
                                   nullptr);
        }

        template<class T>
        void bindVector(std::vector<T> _data)
        {
            bindData(_data.data(), _data.size() * sizeof(T));
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

    class VulkanMaterial : public Material{
    public:
        VulkanMaterial(const std::vector<std::pair<std::string, uint32_t>>& _shaderFiles);

    private:
        std::vector<SP(Shader)> shaders;
    };


} // Flow

#endif //FLOWENGINE_VULKANMATERIAL_H
