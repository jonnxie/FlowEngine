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
        void save(const std::string& _path, uint32_t _index) final;
        std::vector<VkAttachment>& getAttachments() {return m_attachments;};
        VkRenderPass getRenderPass() const {return m_renderPass;}
        VkFramebuffer getFrameBuffer() const {return m_frame_buffer;}
        VkCommandBuffer& getCMD() {return m_cmd;}
    private:
        std::unordered_map<VkFormat, std::pair<VkBuffer, VkDeviceMemory>> m_captureVals;
        VulkanSmartHandle<VkFramebuffer>  m_frame_buffer{VK_NULL_HANDLE};
        std::vector<VkAttachment>       m_attachments{};
        VulkanSmartHandle<VkRenderPass> m_renderPass{VK_NULL_HANDLE};
        bool                            m_released = false;
        VkCommandBuffer                 m_cmd{};
    };

} // Flow

#endif //FLOWENGINE_VULKANFRAMEBUFFER_H
