//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANTOOL_H
#define FLOWENGINE_VULKANTOOL_H

#include <vulkan/vulkan.h>
#include <string>
#include <glm.hpp>
#include <vector>
#include "ktx.h"
#include "ktxvulkan.h"
#include "spirv_reflect.h"

namespace Flow {

    namespace file{
        /*
        * 检测文件是否存在
        */
        bool fileExists(const std::string &filename);

        /*
        *读glsl文件随后创建shader的模块
        */
        std::vector<char> readFile(const std::string &filename);

        /*
         * load .ktx format texture
         */
        ktxResult loadKTXFile(std::string filename, ktxTexture **target);

        unsigned char* loadBinary(std::string fname);
    }

    struct VulkanImageMaterialUnit;

    namespace tool{
        std::string combine(const std::string& _str,int num);

        std::string combineShader(const std::string& _shaderName);

        std::string combineTexture(const std::string& _shaderName);

        std::string combineModel(const std::string& _shaderName);

        std::string combineAnimation(const std::string& _animationName);

        std::string combineB3DM(const std::string& _b3dmName);

        std::string combineI3DM(const std::string& _i3dmName);

        template<class T>
        void printNum(T _num)
        {
            printf("%f\n",_num);
        }

        void printMat(const glm::mat4& _in);

        VkShaderModule createShaderModule(const std::vector<char> &code,VkDevice device);

        VkPipelineShaderStageCreateInfo createShaderStage(const std::string& _filename,uint32_t _type);

        VkDescriptorSetLayoutBinding getSetLayoutBinding(VkDescriptorType _type,VkShaderStageFlags _flags,uint32_t _binding);

        VkBufferCreateInfo getBufferCreateInfo();

        void setLayout(VkCommandBuffer _buffer, VkImage _image, VkImageLayout oldLayout, VkImageLayout newLayout, VkImageSubresourceRange sub);

        VkMemoryAllocateInfo memoryAllocateInfo();

        VkImageCreateInfo imageCreateInfo();

        VkSamplerCreateInfo samplerCreateInfo();

        VkImageViewCreateInfo imageViewCreateInfo();

        VkRenderPassCreateInfo renderPassCreateInfo();

        VkDescriptorPoolSize descriptorPoolSize(VkDescriptorType _type,uint32_t _count);

        VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(VkDescriptorType _type,VkShaderStageFlags _flags,uint32_t _binding,uint32_t _descriptorCount = 1);

        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,uint32_t _maxSetCount);

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding>& _setLayoutBinding);

        VkDescriptorSetAllocateInfo descriptorSetAllocateInfo(VkDescriptorPool _pool,VkDescriptorSetLayout* _layout,uint32_t _count);

        VkDescriptorImageInfo descriptorImageInfo(VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout);

        VkBufferCreateInfo bufferCreateInfo();

        VkBufferCreateInfo bufferCreateInfo(
                VkBufferUsageFlags usage,
                VkDeviceSize size);

        VkViewport viewport(
                float width,
                float height,
                float minDepth,
                float maxDepth);

        VkRect2D rect2D(
                int32_t width,
                int32_t height,
                int32_t offsetX,
                int32_t offsetY);

        VkWriteDescriptorSet writeDescriptorSet(
                VkDescriptorSet dstSet,
                VkDescriptorType type,
                uint32_t binding,
                VkDescriptorBufferInfo* bufferInfo,
                uint32_t descriptorCount = 1);

        VkWriteDescriptorSet writeDescriptorSet(
                VkDescriptorSet dstSet,
                VkDescriptorType type,
                uint32_t binding,
                VkDescriptorImageInfo *imageInfo,
                uint32_t descriptorCount = 1);

        VkPushConstantRange pushConstantRange(
                VkShaderStageFlags stageFlags,
                uint32_t size,
                uint32_t offset);

        VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
                VkPrimitiveTopology topology,
                VkPipelineInputAssemblyStateCreateFlags flags,
                VkBool32 primitiveRestartEnable);

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(
                const VkDescriptorSetLayout* pSetLayouts,
                uint32_t setLayoutCount = 1);

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(
                uint32_t setLayoutCount = 1);

        VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
                VkPolygonMode polygonMode,
                VkCullModeFlags cullMode,
                VkFrontFace frontFace,
                VkPipelineRasterizationStateCreateFlags flags = 0);

        VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(
                VkColorComponentFlags colorWriteMask,
                VkBool32 blendEnable);

        VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(
                uint32_t attachmentCount,
                const VkPipelineColorBlendAttachmentState * pAttachments);

        VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
                VkBool32 depthTestEnable,
                VkBool32 depthWriteEnable,
                VkCompareOp depthCompareOp);

        VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
                uint32_t viewportCount,
                uint32_t scissorCount,
                VkPipelineViewportStateCreateFlags flags = 0);

        VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(
                VkSampleCountFlagBits rasterizationSamples,
                VkPipelineMultisampleStateCreateFlags flags = 0);

        VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
                const VkDynamicState * pDynamicStates,
                uint32_t dynamicStateCount,
                VkPipelineDynamicStateCreateFlags flags = 0);

        VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
                const std::vector<VkDynamicState>& pDynamicStates,
                VkPipelineDynamicStateCreateFlags flags = 0);

        VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo(uint32_t patchControlPoints);

        VkGraphicsPipelineCreateInfo pipelineCreateInfo(
                VkPipelineLayout layout,
                VkRenderPass renderPass,
                VkPipelineCreateFlags flags = 0);

        VkGraphicsPipelineCreateInfo pipelineCreateInfo();

        VkComputePipelineCreateInfo computePipelineCreateInfo(
                VkPipelineLayout layout,
                VkPipelineCreateFlags flags = 0);

        VkVertexInputBindingDescription vertexInputBindingDescription(
                uint32_t binding,
                uint32_t stride,
                VkVertexInputRate inputRate);

        VkVertexInputAttributeDescription vertexInputAttributeDescription(
                uint32_t binding,
                uint32_t location,
                VkFormat format,
                uint32_t offset);

        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo();

        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo(
                const std::vector<VkVertexInputBindingDescription> &vertexBindingDescriptions,
                const std::vector<VkVertexInputAttributeDescription> &vertexAttributeDescriptions
        );

        VkImageMemoryBarrier imageMemoryBarrier();

        void setImageLayout(
                VkCommandBuffer cmdbuffer,
                VkImage image,
                VkImageLayout oldImageLayout,
                VkImageLayout newImageLayout,
                VkImageSubresourceRange subresourceRange,
                VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
        // Uses a fixed sub resource layout with first mip level and layer
        void setImageLayout(
                VkCommandBuffer cmdbuffer,
                VkImage image,
                VkImageAspectFlags aspectMask,
                VkImageLayout oldImageLayout,
                VkImageLayout newImageLayout,
                VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

        uint32_t alignedSize(uint32_t value, uint32_t alignment);

        VkRayTracingPipelineCreateInfoKHR rayTracingPipelineCreateInfoKHR();

        VkAccelerationStructureGeometryKHR accelerationStructureGeometryKHR();

        VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR();

        VkAccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfoKHR();

        VkRayTracingShaderGroupCreateInfoKHR rayTracingShaderGroupCreateInfoKHR();

        VkWriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR();

        VkCommandBufferBeginInfo commandBufferBeginInfo();

        void insertImageMemoryBarrier(
                VkCommandBuffer cmdbuffer,
                VkImage image,
                VkAccessFlags srcAccessMask,
                VkAccessFlags dstAccessMask,
                VkImageLayout oldImageLayout,
                VkImageLayout newImageLayout,
                VkPipelineStageFlags srcStageMask,
                VkPipelineStageFlags dstStageMask,
                VkImageSubresourceRange subresourceRange);

        VkFramebufferCreateInfo framebufferCreateInfo();

        VkRenderPassBeginInfo renderPassBeginInfo();

        uint32_t getMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        VkBufferUsageFlags reflectBufferUsage(SpvReflectDescriptorType _descriptorType);

        VkImageUsageFlags reflectImageUsage(SpvReflectDescriptorType _descriptorType);

        void createBuffer(VkBufferUsageFlags _flags, VkMemoryPropertyFlags _property, VkBuffer& _buffer, VkDeviceMemory& _memory, uint64_t _size);

        VkImageView create2dImageView(VkImage _image, VkFormat _format, VkImageAspectFlagBits _aspectFlags);

        void create2dImage(uint32_t _width,
                           uint32_t _height,
                           VkFormat _format,
                           VkImageTiling _tiling,
                           VkImageUsageFlags _usage,
                           VkMemoryPropertyFlags _properties,
                           VkImage& _image,
                           VkDeviceMemory& _imageMemory);

        void copyBufferToImage(VkCommandBuffer _cb,
                               VkBuffer _buffer,
                               VkImage _image,
                               uint32_t _width,
                               uint32_t _height);

        void reflect2DTexture(const std::string& _filename, VulkanImageMaterialUnit* _materialUnit);

        inline std::string strBool(bool _val){
            return _val? "True":"False";
        }
    }

} // Flow

#endif //FLOWENGINE_VULKANTOOL_H
