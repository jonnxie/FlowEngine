//
// Created by hasee on 2022/6/30.
//

#include "VulkanTool.h"
#include <sstream>
#include <fstream>
#include <vector>
#include "Macro/Macro.h"
#include "ktx.h"
#include "ktxvulkan.h"
#include <cstring>
#include <iostream>
#include "VulkanRendererContext.h"

namespace Flow {

    namespace file{
        bool fileExists(const std::string &filename)
        {
            std::ifstream f(filename.c_str());
            return !f.fail();
        }

        std::vector<char> readFile(const std::string &filename) {
            std::ifstream file(filename, std::ios::ate | std::ios::binary);

            if (!file.is_open()) {
                throw std::runtime_error("failed to open shader file!");
            }

            size_t fileSize = (size_t) file.tellg();
            std::vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(), fileSize);

            file.close();

            return buffer;
        }

        ktxResult loadKTXFile(std::string filename, ktxTexture **target) {
            ktxResult result = KTX_SUCCESS;

            if (!fileExists(filename)) {
                throwFile(filename);
            }
            result = ktxTexture_CreateFromNamedFile(filename.c_str(), KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, target);

            return result;
        }

        unsigned char* loadBinary(std::string fname)
        {
            char    c_file[100];
            strcpy(c_file, fname.c_str());
            FILE * fpPhoto;
            fpPhoto = fopen(c_file, "rb");
            if (fpPhoto == NULL) {
                printf("打开文件失败\n");
            }
            fseek(fpPhoto, 0, SEEK_END);
            long size = ftell(fpPhoto);
            unsigned char* data = (unsigned char*)malloc(size + 1);
            fseek(fpPhoto, 0, SEEK_SET);
            fread(data, size, 1, fpPhoto);
            fclose(fpPhoto);
            return data;
        }
    }



    namespace tool {

        std::string combine(const std::string& _str, int num) {
            std::stringstream str;
            str << num;
            return _str+ str.str();
        }

        std::string combineShader(const std::string& _shaderName){
            return ShaderFilePath + _shaderName;
        }

        std::string combineTexture(const std::string& _shaderName){
            return TextureFilePath + _shaderName;
        }

        std::string combineModel(const std::string& _shaderName){
            return ModelFilePath + _shaderName;
        }

        std::string combineAnimation(const std::string& _animationName){
            return AnimationPath + _animationName;
        }

        std::string combineB3DM(const std::string& _b3dmName){
            return B3DMPath + _b3dmName;
        }

        std::string combineI3DM(const std::string& _i3dmName){
            return I3DMPath + _i3dmName;
        }

        VkPipelineShaderStageCreateInfo createShaderStage(const std::string& _filename,uint32_t _type)
        {
            if(!file::fileExists(_filename)){
                throwFile(_filename);
            }
            auto shader_code = file::readFile(_filename);
            VkPipelineShaderStageCreateInfo shader_info;
            shader_info.pNext = VK_NULL_HANDLE;
            shader_info.flags = 0;
            shader_info.pSpecializationInfo = VK_NULL_HANDLE;
            auto m_shader_module = createShaderModule(shader_code, VulkanDevice);

            shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            switch (_type) {
                case VertexShader:{
                    shader_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
                    break;
                }
                case FragmentShader:{
                    shader_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                    break;
                }
                case ComputeShader:{
                    shader_info.stage = VK_SHADER_STAGE_COMPUTE_BIT;
                    break;
                }
                default: break;
            }
            shader_info.module = m_shader_module;
            shader_info.pName = "main";

            return shader_info;
        }

        VkDescriptorSetLayoutBinding
        getSetLayoutBinding(VkDescriptorType _type, VkShaderStageFlags _flags, uint32_t _binding) {
            return VkDescriptorSetLayoutBinding{_binding, _type, 1, _flags, VK_NULL_HANDLE};
        }

        VkBufferCreateInfo getBufferCreateInfo() {
            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.pNext = nullptr;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            return bufferInfo;
        }

        void setLayout(VkCommandBuffer _buffer, VkImage _image, VkImageLayout oldLayout, VkImageLayout newLayout,
                       VkImageSubresourceRange sub) {
            VkImageMemoryBarrier barrier = {};
            barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            barrier.oldLayout = oldLayout;
            barrier.newLayout = newLayout;
            barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            barrier.image = _image;

            barrier.subresourceRange = sub;

            VkPipelineStageFlags sourceStage;
            VkPipelineStageFlags destinationStage;

            switch (oldLayout) {
                case VK_IMAGE_LAYOUT_UNDEFINED:
                    // Image layout is undefined (or does not matter).
                    // Only valid as initial layout. No flags required.
                    barrier.srcAccessMask = 0;
                    break;

                case VK_IMAGE_LAYOUT_PREINITIALIZED:
                    // Image is preinitialized.
                    // Only valid as initial layout for linear images; preserves memory
                    // contents. Make sure host writes have finished.
                    barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                    // Image is a color attachment.
                    // Make sure writes to the color buffer have finished
                    barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                    // Image is a depth/stencil attachment.
                    // Make sure any writes to the depth/stencil buffer have finished.
                    barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                    // Image is a transfer source.
                    // Make sure any reads from the image have finished
                    barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                    break;

                case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                    // Image is a transfer destination.
                    // Make sure any writes to the image have finished.
                    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                    // Image is read by a shader.
                    // Make sure any shader reads from the image have finished
                    barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
                    break;

                default:
                    /* Value not used by callers, so not supported. */
                    assert(KTX_FALSE);
            }

            // Target layouts (new)
            // The destination access mask controls the dependency for the new image
            // layout.
            switch (newLayout) {
                case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                    // Image will be used as a transfer destination.
                    // Make sure any writes to the image have finished.
                    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                    // Image will be used as a transfer source.
                    // Make sure any reads from and writes to the image have finished.
                    barrier.srcAccessMask |= VK_ACCESS_TRANSFER_READ_BIT;
                    barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                    break;

                case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                    // Image will be used as a color attachment.
                    // Make sure any writes to the color buffer have finished.
                    barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                    barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                    // Image layout will be used as a depth/stencil attachment.
                    // Make sure any writes to depth/stencil buffer have finished.
                    barrier.dstAccessMask
                            = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                    // Image will be read in a shader (sampler, input attachment).
                    // Make sure any writes to the image have finished.
                    if (barrier.srcAccessMask == 0) {
                        barrier.srcAccessMask
                                = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
                    }
                    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
                    break;
                default:
                    /* Value not used by callers, so not supported. */
                    assert(KTX_FALSE);
            }
            vkCmdPipelineBarrier(
                    _buffer,
                    sourceStage, destinationStage,
                    0,
                    0, nullptr,
                    0, nullptr,
                    1, &barrier
            );
        }

        VkMemoryAllocateInfo memoryAllocateInfo() {
            VkMemoryAllocateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            info.pNext = VK_NULL_HANDLE;
            return info;
        }

        VkImageCreateInfo imageCreateInfo() {
            VkImageCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            info.pNext = VK_NULL_HANDLE;
            return info;
        }

        VkSamplerCreateInfo samplerCreateInfo() {
            VkSamplerCreateInfo samplerCreateInfo {};
            samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            samplerCreateInfo.maxAnisotropy = 1.0f;
            return samplerCreateInfo;
        }

        VkImageViewCreateInfo imageViewCreateInfo()
        {
            VkImageViewCreateInfo viewCreateInfo = {};
            viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewCreateInfo.pNext = VK_NULL_HANDLE;
            return viewCreateInfo;
        }

        VkRenderPassCreateInfo renderPassCreateInfo()
        {
            VkRenderPassCreateInfo renderPassCreateInfo {};
            renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            return renderPassCreateInfo;
        }

        VkDescriptorPoolSize descriptorPoolSize(VkDescriptorType _type,uint32_t _count)
        {
//        VkDescriptorPoolSize poolSize = {};
//        poolSize.type = _type;
//        poolSize.descriptorCount = _count;
            return VkDescriptorPoolSize{_type,_count};
        }

        VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(VkDescriptorType _type,VkShaderStageFlags _flags,uint32_t _binding,uint32_t _descriptorCount)
        {
            VkDescriptorSetLayoutBinding setLayoutBinding {};
            setLayoutBinding.descriptorType = _type;
            setLayoutBinding.stageFlags = _flags;
            setLayoutBinding.binding = _binding;
            setLayoutBinding.descriptorCount = _descriptorCount;
            return setLayoutBinding;
        }

        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes,uint32_t _maxSetCount)
        {
            VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
            descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            descriptorPoolInfo.pNext = VK_NULL_HANDLE;
            descriptorPoolInfo.maxSets = _maxSetCount;
            descriptorPoolInfo.poolSizeCount = poolSizes.size();
            descriptorPoolInfo.pPoolSizes = poolSizes.data();
            return descriptorPoolInfo;
        }

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding> &_setLayoutBinding) {
            VkDescriptorSetLayoutCreateInfo descriptorLayout = {};
            descriptorLayout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            descriptorLayout.pNext = VK_NULL_HANDLE;
            descriptorLayout.bindingCount = _setLayoutBinding.size();
            descriptorLayout.pBindings = _setLayoutBinding.data();
            return descriptorLayout;
        }

        VkDescriptorSetAllocateInfo
        descriptorSetAllocateInfo(VkDescriptorPool _pool, VkDescriptorSetLayout *_layout, uint32_t _count) {
            return VkDescriptorSetAllocateInfo{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                                               VK_NULL_HANDLE,
                                               _pool,
                                               _count,
                                               _layout};
        }

        VkDescriptorImageInfo descriptorImageInfo(VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout) {
            VkDescriptorImageInfo descriptorImageInfo {};
            descriptorImageInfo.sampler = sampler;
            descriptorImageInfo.imageView = imageView;
            descriptorImageInfo.imageLayout = imageLayout;
            return descriptorImageInfo;
        }

        VkWriteDescriptorSet writeDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, uint32_t binding,
                                                VkDescriptorBufferInfo *bufferInfo, uint32_t descriptorCount) {
            VkWriteDescriptorSet writeDescriptorSet {};
            writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writeDescriptorSet.dstSet = dstSet;
            writeDescriptorSet.descriptorType = type;
            writeDescriptorSet.dstBinding = binding;
            writeDescriptorSet.pBufferInfo = bufferInfo;
            writeDescriptorSet.descriptorCount = descriptorCount;
            return writeDescriptorSet;
        }

        VkWriteDescriptorSet writeDescriptorSet(VkDescriptorSet dstSet, VkDescriptorType type, uint32_t binding,
                                                VkDescriptorImageInfo *imageInfo, uint32_t descriptorCount) {
            VkWriteDescriptorSet writeDescriptorSet {};
            writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writeDescriptorSet.dstSet = dstSet;
            writeDescriptorSet.descriptorType = type;
            writeDescriptorSet.dstBinding = binding;
            writeDescriptorSet.pImageInfo = imageInfo;
            writeDescriptorSet.descriptorCount = descriptorCount;
            return writeDescriptorSet;
        }

        VkPushConstantRange pushConstantRange(VkShaderStageFlags stageFlags, uint32_t size, uint32_t offset) {
            VkPushConstantRange pushConstantRange {};
            pushConstantRange.stageFlags = stageFlags;
            pushConstantRange.offset = offset;
            pushConstantRange.size = size;
            return pushConstantRange;
        }

        VkPipelineInputAssemblyStateCreateInfo
        pipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology, VkPipelineInputAssemblyStateCreateFlags flags,
                                             VkBool32 primitiveRestartEnable) {
            VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo {};
            pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            pipelineInputAssemblyStateCreateInfo.topology = topology;
            pipelineInputAssemblyStateCreateInfo.flags = flags;
            pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = primitiveRestartEnable;
            return pipelineInputAssemblyStateCreateInfo;
        }

        VkPipelineLayoutCreateInfo
        pipelineLayoutCreateInfo(const VkDescriptorSetLayout *pSetLayouts, uint32_t setLayoutCount) {
            VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {};
            pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
            pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
            pipelineLayoutCreateInfo.pSetLayouts = pSetLayouts;
            return pipelineLayoutCreateInfo;
        }

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(uint32_t setLayoutCount) {
            VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
            pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
            pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
            return pipelineLayoutCreateInfo;
        }

        VkPipelineRasterizationStateCreateInfo
        pipelineRasterizationStateCreateInfo(VkPolygonMode polygonMode, VkCullModeFlags cullMode, VkFrontFace frontFace,
                                             VkPipelineRasterizationStateCreateFlags flags) {
            VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo {};
            pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            pipelineRasterizationStateCreateInfo.polygonMode = polygonMode;
            pipelineRasterizationStateCreateInfo.cullMode = cullMode;
            pipelineRasterizationStateCreateInfo.frontFace = frontFace;
            pipelineRasterizationStateCreateInfo.flags = flags;
            pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
            pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
            return pipelineRasterizationStateCreateInfo;
        }

        VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(
                VkColorComponentFlags colorWriteMask,
                VkBool32 blendEnable)
        {
            VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState {};
            pipelineColorBlendAttachmentState.colorWriteMask = colorWriteMask;
            pipelineColorBlendAttachmentState.blendEnable = blendEnable;
            return pipelineColorBlendAttachmentState;
        }

        VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(uint32_t attachmentCount,
                                                                              const VkPipelineColorBlendAttachmentState *pAttachments) {
            VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo {};
            pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            pipelineColorBlendStateCreateInfo.attachmentCount = attachmentCount;
            pipelineColorBlendStateCreateInfo.pAttachments = pAttachments;
            return pipelineColorBlendStateCreateInfo;
        }

        VkPipelineDepthStencilStateCreateInfo
        pipelineDepthStencilStateCreateInfo(VkBool32 depthTestEnable, VkBool32 depthWriteEnable,
                                            VkCompareOp depthCompareOp) {
            VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo {};
            pipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
            pipelineDepthStencilStateCreateInfo.depthTestEnable = depthTestEnable;
            pipelineDepthStencilStateCreateInfo.depthWriteEnable = depthWriteEnable;
            pipelineDepthStencilStateCreateInfo.depthCompareOp = depthCompareOp;
            pipelineDepthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
            return pipelineDepthStencilStateCreateInfo;
        }

        VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(uint32_t viewportCount, uint32_t scissorCount,
                                                                          VkPipelineViewportStateCreateFlags flags) {
            VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo {};
            pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            pipelineViewportStateCreateInfo.viewportCount = viewportCount;
            pipelineViewportStateCreateInfo.scissorCount = scissorCount;
            pipelineViewportStateCreateInfo.flags = flags;
            return pipelineViewportStateCreateInfo;
        }

        VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(VkSampleCountFlagBits rasterizationSamples,
                                                                                VkPipelineMultisampleStateCreateFlags flags) {
            VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo {};
            pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            pipelineMultisampleStateCreateInfo.rasterizationSamples = rasterizationSamples;
            pipelineMultisampleStateCreateInfo.flags = flags;
            return pipelineMultisampleStateCreateInfo;
        }

        VkPipelineDynamicStateCreateInfo
        pipelineDynamicStateCreateInfo(const VkDynamicState *pDynamicStates, uint32_t dynamicStateCount,
                                       VkPipelineDynamicStateCreateFlags flags) {
            VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo {};
            pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates;
            pipelineDynamicStateCreateInfo.dynamicStateCount = dynamicStateCount;
            pipelineDynamicStateCreateInfo.flags = flags;
            return pipelineDynamicStateCreateInfo;
        }

        VkPipelineDynamicStateCreateInfo
        pipelineDynamicStateCreateInfo(const std::vector<VkDynamicState> &pDynamicStates,
                                       VkPipelineDynamicStateCreateFlags flags) {
            VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
            pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates.data();
            pipelineDynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(pDynamicStates.size());
            pipelineDynamicStateCreateInfo.flags = flags;
            return pipelineDynamicStateCreateInfo;
        }

        VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo(uint32_t patchControlPoints) {
            VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo {};
            pipelineTessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
            pipelineTessellationStateCreateInfo.patchControlPoints = patchControlPoints;
            return pipelineTessellationStateCreateInfo;
        }

        VkGraphicsPipelineCreateInfo
        pipelineCreateInfo(VkPipelineLayout layout, VkRenderPass renderPass, VkPipelineCreateFlags flags) {
            VkGraphicsPipelineCreateInfo pipelineCreateInfo {};
            pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            pipelineCreateInfo.layout = layout;
            pipelineCreateInfo.renderPass = renderPass;
            pipelineCreateInfo.flags = flags;
            pipelineCreateInfo.basePipelineIndex = -1;
            pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
            return pipelineCreateInfo;
        }

        VkGraphicsPipelineCreateInfo pipelineCreateInfo() {
            VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
            pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            pipelineCreateInfo.basePipelineIndex = -1;
            pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
            return pipelineCreateInfo;
        }

        VkComputePipelineCreateInfo computePipelineCreateInfo(VkPipelineLayout layout, VkPipelineCreateFlags flags) {
            VkComputePipelineCreateInfo computePipelineCreateInfo {};
            computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
            computePipelineCreateInfo.layout = layout;
            computePipelineCreateInfo.flags = flags;
            return computePipelineCreateInfo;
        }

        VkVertexInputBindingDescription
        vertexInputBindingDescription(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) {
            VkVertexInputBindingDescription vInputBindDescription {};
            vInputBindDescription.binding = binding;
            vInputBindDescription.stride = stride;
            vInputBindDescription.inputRate = inputRate;
            return vInputBindDescription;
        }

        VkVertexInputAttributeDescription
        vertexInputAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset) {
            VkVertexInputAttributeDescription vInputAttribDescription {};
            vInputAttribDescription.location = location;
            vInputAttribDescription.binding = binding;
            vInputAttribDescription.format = format;
            vInputAttribDescription.offset = offset;
            return vInputAttribDescription;
        }

        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo() {
            VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo {};
            pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            return pipelineVertexInputStateCreateInfo;
        }

        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo(
                const std::vector<VkVertexInputBindingDescription> &vertexBindingDescriptions,
                const std::vector<VkVertexInputAttributeDescription> &vertexAttributeDescriptions) {
            VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
            pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions.size());
            pipelineVertexInputStateCreateInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();
            pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributeDescriptions.size());
            pipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();
            return pipelineVertexInputStateCreateInfo;
        }

        VkImageMemoryBarrier imageMemoryBarrier() {
            VkImageMemoryBarrier imageMemoryBarrier {};
            imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            return imageMemoryBarrier;
        }


        void setImageLayout(
                VkCommandBuffer cmdbuffer,
                VkImage image,
                VkImageLayout oldImageLayout,
                VkImageLayout newImageLayout,
                VkImageSubresourceRange subresourceRange,
                VkPipelineStageFlags srcStageMask,
                VkPipelineStageFlags dstStageMask)
        {
            // Create an image barrier object
            VkImageMemoryBarrier imageMemoryBarrier = tool::imageMemoryBarrier();
            imageMemoryBarrier.oldLayout = oldImageLayout;
            imageMemoryBarrier.newLayout = newImageLayout;
            imageMemoryBarrier.image = image;
            imageMemoryBarrier.subresourceRange = subresourceRange;

            // Source layouts (old)
            // Source access mask controls actions that have to be finished on the old layout
            // before it will be transitioned to the new layout
            switch (oldImageLayout)
            {
                case VK_IMAGE_LAYOUT_UNDEFINED:
                    // Image layout is undefined (or does not matter)
                    // Only valid as initial layout
                    // No flags required, listed only for completeness
                    imageMemoryBarrier.srcAccessMask = 0;
                    break;

                case VK_IMAGE_LAYOUT_PREINITIALIZED:
                    // Image is preinitialized
                    // Only valid as initial layout for linear images, preserves memory contents
                    // Make sure host writes have been finished
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                    // Image is a color attachment
                    // Make sure any writes to the color buffer have been finished
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                    // Image is a depth/stencil attachment
                    // Make sure any writes to the depth/stencil buffer have been finished
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                    // Image is a transfer source
                    // Make sure any reads from the image have been finished
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                    break;

                case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                    // Image is a transfer destination
                    // Make sure any writes to the image have been finished
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                    // Image is read by a shader
                    // Make sure any shader reads from the image have been finished
                    imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
                    break;
                default:
                    // Other source layouts aren't handled (yet)
                    break;
            }

            // Target layouts (new)
            // Destination access mask controls the dependency for the new image layout
            switch (newImageLayout)
            {
                case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
                    // Image will be used as a transfer destination
                    // Make sure any writes to the image have been finished
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
                    // Image will be used as a transfer source
                    // Make sure any reads from the image have been finished
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                    break;

                case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                    // Image will be used as a color attachment
                    // Make sure any writes to the color buffer have been finished
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
                    // Image layout will be used as a depth/stencil attachment
                    // Make sure any writes to depth/stencil buffer have been finished
                    imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                    break;

                case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                    // Image will be read in a shader (sampler, input attachment)
                    // Make sure any writes to the image have been finished
                    if (imageMemoryBarrier.srcAccessMask == 0)
                    {
                        imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
                    }
                    imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
                    break;
                default:
                    // Other source layouts aren't handled (yet)
                    break;
            }

            // Put barrier inside setup command buffer
            vkCmdPipelineBarrier(
                    cmdbuffer,
                    srcStageMask,
                    dstStageMask,
                    0,
                    0, nullptr,
                    0, nullptr,
                    1, &imageMemoryBarrier);
        }

        // Fixed sub resource on first mip level and layer
        void setImageLayout(
                VkCommandBuffer cmdbuffer,
                VkImage image,
                VkImageAspectFlags aspectMask,
                VkImageLayout oldImageLayout,
                VkImageLayout newImageLayout,
                VkPipelineStageFlags srcStageMask,
                VkPipelineStageFlags dstStageMask)
        {
            VkImageSubresourceRange subresourceRange = {};
            subresourceRange.aspectMask = aspectMask;
            subresourceRange.baseMipLevel = 0;
            subresourceRange.levelCount = 1;
            subresourceRange.layerCount = 1;
            setImageLayout(cmdbuffer, image, oldImageLayout, newImageLayout, subresourceRange, srcStageMask, dstStageMask);
        }

        VkViewport viewport(float width, float height, float minDepth, float maxDepth) {
            VkViewport viewport {};
            viewport.width = width;
            viewport.height = height;
            viewport.minDepth = minDepth;
            viewport.maxDepth = maxDepth;
            return viewport;
        }

        VkRect2D rect2D(
                int32_t width,
                int32_t height,
                int32_t offsetX,
                int32_t offsetY) {
            VkRect2D rect2D {};
            rect2D.extent.width = width;
            rect2D.extent.height = height;
            rect2D.offset.x = offsetX;
            rect2D.offset.y = offsetY;
            return rect2D;
        }

        uint32_t alignedSize(uint32_t value, uint32_t alignment) {
            return (value + alignment - 1) & ~(alignment - 1);
        }

        VkBufferCreateInfo bufferCreateInfo() {
            VkBufferCreateInfo bufCreateInfo {};
            bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            return bufCreateInfo;
        }

        VkBufferCreateInfo bufferCreateInfo(VkBufferUsageFlags usage, VkDeviceSize size) {
            VkBufferCreateInfo bufCreateInfo {};
            bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufCreateInfo.usage = usage;
            bufCreateInfo.size = size;
            return bufCreateInfo;
        }

        VkAccelerationStructureGeometryKHR accelerationStructureGeometryKHR() {
            VkAccelerationStructureGeometryKHR accelerationStructureGeometryKHR{};
            accelerationStructureGeometryKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
            return accelerationStructureGeometryKHR;
        }

        VkRayTracingPipelineCreateInfoKHR rayTracingPipelineCreateInfoKHR() {
            VkRayTracingPipelineCreateInfoKHR rayTracingPipelineCreateInfoKHR{};
            rayTracingPipelineCreateInfoKHR.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
            return rayTracingPipelineCreateInfoKHR;
        }

        VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR() {
            VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfoKHR{};
            accelerationStructureBuildGeometryInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
            return accelerationStructureBuildGeometryInfoKHR;
        }

        VkAccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfoKHR() {
            VkAccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfoKHR{};
            accelerationStructureBuildSizesInfoKHR.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
            return accelerationStructureBuildSizesInfoKHR;
        }

        VkRayTracingShaderGroupCreateInfoKHR rayTracingShaderGroupCreateInfoKHR() {
            VkRayTracingShaderGroupCreateInfoKHR rayTracingShaderGroupCreateInfoKHR{};
            rayTracingShaderGroupCreateInfoKHR.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
            return rayTracingShaderGroupCreateInfoKHR;
        }

        VkWriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR() {
            VkWriteDescriptorSetAccelerationStructureKHR writeDescriptorSetAccelerationStructureKHR{};
            writeDescriptorSetAccelerationStructureKHR.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
            return writeDescriptorSetAccelerationStructureKHR;
        }

        VkCommandBufferBeginInfo commandBufferBeginInfo() {
            VkCommandBufferBeginInfo cmdBufferBeginInfo {};
            cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            return cmdBufferBeginInfo;
        }

        void insertImageMemoryBarrier(VkCommandBuffer cmdbuffer, VkImage image, VkAccessFlags srcAccessMask,
                                      VkAccessFlags dstAccessMask, VkImageLayout oldImageLayout,
                                      VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask,
                                      VkPipelineStageFlags dstStageMask, VkImageSubresourceRange subresourceRange) {
            VkImageMemoryBarrier imageMemoryBarrier = tool::imageMemoryBarrier();
            imageMemoryBarrier.srcAccessMask = srcAccessMask;
            imageMemoryBarrier.dstAccessMask = dstAccessMask;
            imageMemoryBarrier.oldLayout = oldImageLayout;
            imageMemoryBarrier.newLayout = newImageLayout;
            imageMemoryBarrier.image = image;
            imageMemoryBarrier.subresourceRange = subresourceRange;

            vkCmdPipelineBarrier(
                    cmdbuffer,
                    srcStageMask,
                    dstStageMask,
                    0,
                    0, nullptr,
                    0, nullptr,
                    1, &imageMemoryBarrier);
        }

        VkFramebufferCreateInfo framebufferCreateInfo(){
            VkFramebufferCreateInfo framebufferCreateInfo {};
            framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            return framebufferCreateInfo;
        }

        VkRenderPassBeginInfo renderPassBeginInfo() {
            VkRenderPassBeginInfo renderPassBeginInfo {};
            renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            return renderPassBeginInfo;
        }

        uint32_t getMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
        {
            VkPhysicalDeviceMemoryProperties memProperties = VulkanPhysicalDeviceMemoryProperties;

            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i)) &&
                    (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                    return i;
                }
            }
            throw std::runtime_error("failed to find suitable memory type!");
        }

        void printMat(const glm::mat4& _in) {
            printf("[%f,%f,%f,%f]\n",_in[0][0],_in[0][1],_in[0][2],_in[0][3]);
            printf("[%f,%f,%f,%f]\n",_in[1][0],_in[1][1],_in[1][2],_in[1][3]);
            printf("[%f,%f,%f,%f]\n",_in[2][0],_in[2][1],_in[2][2],_in[2][3]);
            printf("[%f,%f,%f,%f]\n",_in[3][0],_in[3][1],_in[3][2],_in[3][3]);
        }

        VkShaderModule createShaderModule(const std::vector<char> &code,VkDevice device) {
            VkShaderModuleCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = code.size();

            createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

            VkShaderModule shaderModule;
            if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
                throw std::runtime_error("failed to create shader module!");
            }

            return shaderModule;
        }

    }


} // Flow