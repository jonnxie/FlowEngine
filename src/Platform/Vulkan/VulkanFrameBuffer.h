//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANFRAMEBUFFER_H
#define FLOWENGINE_VULKANFRAMEBUFFER_H

#include <vulkan/vulkan.h>
#include <unordered_map>
#include "Render/FrameBuffer.h"
#include "VulkanSmartHandle.h"

namespace Flow {

    struct VkAttachment{
        VkImage                 image;
        VkImageView             imageView;
        VkDeviceMemory          memory;
        VkFormat                format;
        VkSampler               sampler;
        VkDescriptorImageInfo   descriptor;
    };

    struct VulkanFrameBufferSpecification : public FrameBufferSpecification{
        VkRenderPass renderPass{VK_NULL_HANDLE};
    };

    class VulkanFrameBuffer : public FrameBuffer{
    public:
        explicit VulkanFrameBuffer(UP(VulkanFrameBufferSpecification) _spec);
        ~VulkanFrameBuffer() override = default;
        void init();
        void resize(uint32_t _width,uint32_t _height) final;
        void release() final;
        void releaseCaptureVals() final;
        std::vector<VkAttachment>& getAttachments() {return m_attachments;};
    private:
        std::unordered_map<VkFormat, std::pair<VkBuffer, VkDeviceMemory>> m_captureVals;
        SP(VulkanSmartHandle<VkFramebuffer>)                m_frame_buffer{};
        std::vector<VkAttachment>       m_attachments{};
        bool                            m_released = false;
    };

} // Flow

#endif //FLOWENGINE_VULKANFRAMEBUFFER_H
