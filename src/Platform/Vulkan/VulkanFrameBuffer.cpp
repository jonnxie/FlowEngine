//
// Created by hasee on 2022/6/30.
//

#include "VulkanFrameBuffer.h"
#include "VulkanRendererContext.h"
#include "VulkanFormat.h"
#include "VulkanTool.h"
#include <string>
#include <cstring>
#include <fstream>

namespace Flow {

    VkImageAspectFlags getAspect(VkImageUsageFlags _usage)
    {
        VkFlags flags = 0x00000000;
        if(_usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) flags |= VK_IMAGE_ASPECT_COLOR_BIT;

        if(_usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) flags |= VK_IMAGE_ASPECT_DEPTH_BIT;

        return VkImageAspectFlags(flags);
    }

    void VulkanFrameBuffer::resize(uint32_t _width, uint32_t _height) {
        m_spec->Width = _width;
        m_spec->Height = _height;
        release();
        init();
    }

    void VulkanFrameBuffer::release() {
        VkDevice device = VulkanDevice;
        for(auto& a : m_attachments)
        {
            vkDestroyImageView(device, a.imageView, nullptr);
            vkDestroyImage(device, a.image,nullptr);
            vkFreeMemory(device, a.memory, nullptr);
            vkDestroySampler(device, a.sampler, nullptr);
        }

        m_frame_buffer->release();
        m_released = true;
    }

    void VulkanFrameBuffer::releaseCaptureVals() {

    }

    VulkanFrameBuffer::VulkanFrameBuffer(UP(VulkanFrameBufferSpecification) _spec) :
    FrameBuffer(std::move(_spec))
    {
        init();
    }

    void VulkanFrameBuffer::save(const std::string& _path, uint32_t _index) {
        bool supportsBlit = true;
        auto physicalDevice = VulkanPhysicalDevice;
        auto logicalDevice = VulkanDevice;
        VkFormatProperties formatProps;

        vkGetPhysicalDeviceFormatProperties(physicalDevice, generateFormat(m_spec->formats[_index].format), &formatProps);
        if (!(formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)) {
            std::cerr << "Device does not support blitting from optimal tiled images, using copy instead of blit!" << std::endl;
            supportsBlit = false;
        }

        vkGetPhysicalDeviceFormatProperties(physicalDevice, VK_FORMAT_R8G8B8A8_UNORM, &formatProps);
        if (!(formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)) {
            std::cerr << "Device does not support blitting to linear tiled images, using copy instead of blit!" << std::endl;
            supportsBlit = false;
        }

        VkImage srcImage = m_attachments[_index].image;

        // Create the linear tiled destination image to copy to and to read the memory from
        VkImageCreateInfo imageCreateCI(tool::imageCreateInfo());
        imageCreateCI.imageType = VK_IMAGE_TYPE_2D;
        // Note that vkCmdBlitImage (if supported) will also do format conversions if the swapchain color format would differ
        imageCreateCI.format = VK_FORMAT_R8G8B8A8_UNORM;
        imageCreateCI.extent.width = RendererContext::get()->getPresentExtent().first;
        imageCreateCI.extent.height = RendererContext::get()->getPresentExtent().second;
        imageCreateCI.extent.depth = 1;
        imageCreateCI.arrayLayers = 1;
        imageCreateCI.mipLevels = 1;
        imageCreateCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageCreateCI.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCreateCI.tiling = VK_IMAGE_TILING_LINEAR;
        imageCreateCI.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        // Create the image
        VkImage dstImage;
        vkCreateImage(logicalDevice, &imageCreateCI, nullptr, &dstImage);

        VkMemoryRequirements memRequirements;
        VkMemoryAllocateInfo memAllocInfo(tool::memoryAllocateInfo());
        VkDeviceMemory dstImageMemory;
        vkGetImageMemoryRequirements(logicalDevice, dstImage, &memRequirements);
        memAllocInfo.allocationSize = memRequirements.size;
        // Memory must be host visible to copy from
        memAllocInfo.memoryTypeIndex = tool::getMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        vkAllocateMemory(logicalDevice, &memAllocInfo, nullptr, &dstImageMemory);
        vkBindImageMemory(logicalDevice, dstImage, dstImageMemory, 0);

        VkCommandBuffer copyCmd = VulkanContext->beginSingleCommandBuffer();

        // Transition destination image to transfer destination layout
        tool::insertImageMemoryBarrier(
                copyCmd,
                dstImage,
                0,
                VK_ACCESS_TRANSFER_WRITE_BIT,
                VK_IMAGE_LAYOUT_UNDEFINED,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

        // Transition swapchain image from present to transfer source layout
        tool::insertImageMemoryBarrier(
                copyCmd,
                srcImage,
                VK_ACCESS_MEMORY_READ_BIT,
                VK_ACCESS_TRANSFER_READ_BIT,
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

        if (supportsBlit)
        {
            // Define the region to blit (we will blit the whole swapchain image)
            VkOffset3D blitSize;
            blitSize.x = RendererContext::get()->getPresentExtent().first;
            blitSize.y = RendererContext::get()->getPresentExtent().second;
            blitSize.z = 1;
            VkImageBlit imageBlitRegion{};
            imageBlitRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageBlitRegion.srcSubresource.layerCount = 1;
            imageBlitRegion.srcOffsets[1] = blitSize;
            imageBlitRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageBlitRegion.dstSubresource.layerCount = 1;
            imageBlitRegion.dstOffsets[1] = blitSize;

            // Issue the blit command
            vkCmdBlitImage(
                    copyCmd,
                    srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                    dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    1,
                    &imageBlitRegion,
                    VK_FILTER_NEAREST);
        }
        else
        {
            // Otherwise use image copy (requires us to manually flip components)
            VkImageCopy imageCopyRegion{};
            imageCopyRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageCopyRegion.srcSubresource.layerCount = 1;
            imageCopyRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageCopyRegion.dstSubresource.layerCount = 1;
            imageCopyRegion.extent.width = RendererContext::get()->getPresentExtent().first;
            imageCopyRegion.extent.height = RendererContext::get()->getPresentExtent().second;
            imageCopyRegion.extent.depth = 1;

            // Issue the copy command
            vkCmdCopyImage(
                    copyCmd,
                    srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                    dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    1,
                    &imageCopyRegion);
        }

        // Transition destination image to general layout, which is the required layout for mapping the image memory later on
        tool::insertImageMemoryBarrier(
                copyCmd,
                dstImage,
                VK_ACCESS_TRANSFER_WRITE_BIT,
                VK_ACCESS_MEMORY_READ_BIT,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_IMAGE_LAYOUT_GENERAL,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

        // Transition back the swap chain image after the blit is done
        tool::insertImageMemoryBarrier(
                copyCmd,
                srcImage,
                VK_ACCESS_TRANSFER_READ_BIT,
                VK_ACCESS_MEMORY_READ_BIT,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VkImageSubresourceRange{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

        VulkanContext->endSingleCommandBuffer(copyCmd);

        VkImageSubresource subResource { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0 };
        VkSubresourceLayout subResourceLayout;
        vkGetImageSubresourceLayout(logicalDevice, dstImage, &subResource, &subResourceLayout);

        // Map image memory so we can start copying from it
        const char* data;
        vkMapMemory(logicalDevice, dstImageMemory, 0, VK_WHOLE_SIZE, 0, (void**)&data);
        data += subResourceLayout.offset;

        std::ofstream file(_path, std::ios::out | std::ios::binary);

        // ppm header
        file << "P6\n" << RendererContext::get()->getPresentExtent().first << "\n" << RendererContext::get()->getPresentExtent().second << "\n" << 255 << "\n";

        // If source is BGR (destination is always RGB) and we can't use blit (which does automatic conversion), we'll have to manually swizzle color components
        bool colorSwizzle = false;
        // Check if source is BGR
        // Note: Not complete, only contains most common and basic BGR surface formats for demonstration purposes
        if (!supportsBlit)
        {
            std::vector<VkFormat> formatsBGR = { VK_FORMAT_B8G8R8A8_SRGB, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_B8G8R8A8_SNORM };
            colorSwizzle = (std::find(formatsBGR.begin(), formatsBGR.end(), generateFormat(m_spec->formats[_index].format)) != formatsBGR.end());
        }

        // ppm binary pixel data
        for (uint32_t y = 0; y < RendererContext::get()->getPresentExtent().second; y++)
        {
            unsigned int *row = (unsigned int*)data;
            for (uint32_t x = 0; x < RendererContext::get()->getPresentExtent().second; x++)
            {
                if (colorSwizzle)
                {
                    file.write((char*)row+2, 1);
                    file.write((char*)row+1, 1);
                    file.write((char*)row, 1);
                }
                else
                {
                    file.write((char*)row, 3);
                }
                row++;
            }
            data += subResourceLayout.rowPitch;
        }
        file.close();

        std::cout << "Screenshot saved to disk" << std::endl;

        // Clean up resources
        vkUnmapMemory(logicalDevice, dstImageMemory);
        vkFreeMemory(logicalDevice, dstImageMemory, nullptr);
        vkDestroyImage(logicalDevice, dstImage, nullptr);

    }

    void VulkanFrameBuffer::init() {
        VkDevice device = VulkanDevice;
        m_attachments.resize(m_spec->formats.size());
        for(size_t index = 0; index < m_spec->formats.size(); index++)
        {
            m_attachments[index].format = generateFormat(m_spec->formats[index].format);
            VkImageCreateInfo image = tool::imageCreateInfo();
            image.imageType = VK_IMAGE_TYPE_2D;
            image.format = m_attachments[index].format;
            image.extent.width = m_spec->Width;
            image.extent.height = m_spec->Height;
            image.extent.depth = 1;
            image.mipLevels = 1;
            image.arrayLayers = 1;
            image.samples = VkSampleCountFlagBits(1 << (m_spec->Samples - 1));
            image.tiling = VK_IMAGE_TILING_OPTIMAL;
            image.usage = getUsage(m_spec->formats[index].usage) | VK_IMAGE_USAGE_SAMPLED_BIT;

            VkMemoryAllocateInfo memAlloc = tool::memoryAllocateInfo();
            VkMemoryRequirements memReqs;

            vkCreateImage(device, &image, nullptr, &m_attachments[index].image);
            vkGetImageMemoryRequirements(device, m_attachments[index].image, &memReqs);
            memAlloc.allocationSize = memReqs.size;
            memAlloc.memoryTypeIndex = tool::getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            vkAllocateMemory(device, &memAlloc, nullptr, &m_attachments[index].memory);
            vkBindImageMemory(device, m_attachments[index].image, m_attachments[index].memory, 0);

            VkImageViewCreateInfo colorImageView = tool::imageViewCreateInfo();
            colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
            colorImageView.format = m_attachments[index].format;
            colorImageView.subresourceRange = {};
            colorImageView.subresourceRange.aspectMask = getAspect(getUsage(m_spec->formats[index].usage));
            colorImageView.subresourceRange.baseMipLevel = 0;
            colorImageView.subresourceRange.levelCount = 1;
            colorImageView.subresourceRange.baseArrayLayer = 0;
            colorImageView.subresourceRange.layerCount = 1;
            colorImageView.image = m_attachments[index].image;
            vkCreateImageView(device, &colorImageView, nullptr, &m_attachments[index].imageView);

            // Create sampler to sample from the attachment in the fragment shader
            VkSamplerCreateInfo samplerInfo = tool::samplerCreateInfo();
            samplerInfo.magFilter = VK_FILTER_LINEAR;
            samplerInfo.minFilter = VK_FILTER_LINEAR;
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            samplerInfo.addressModeV = samplerInfo.addressModeU;
            samplerInfo.addressModeW = samplerInfo.addressModeU;
            samplerInfo.mipLodBias = 0.0f;
            samplerInfo.maxAnisotropy = 1.0f;
            samplerInfo.minLod = 0.0f;
            samplerInfo.maxLod = 1.0f;
            samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
            vkCreateSampler(device, &samplerInfo, nullptr, &m_attachments[index].sampler);

            m_attachments[index].descriptor = {m_attachments[index].sampler, m_attachments[index].imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
        }

        std::vector<VkImageView> attachments{};
        for(auto & a: m_attachments)
        {
            attachments.emplace_back(a.imageView);
        }

        VkFramebufferCreateInfo info = tool::framebufferCreateInfo();
        info.renderPass = ((VulkanFrameBufferSpecification*)m_spec.get())->renderPass;
        info.attachmentCount = attachments.size();
        info.pAttachments = attachments.data();
        info.width = m_spec->Width;
        info.height = m_spec->Height;
        info.layers = 1;

        VkFramebuffer framebuffer;
        vkCreateFramebuffer(device, &info, nullptr, &framebuffer);
        m_frame_buffer = std::make_shared<VulkanSmartHandle<VkFramebuffer>>(framebuffer);
    }
} // Flow