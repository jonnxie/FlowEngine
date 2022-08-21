//
// Created by hasee on 2022/7/7.
//

#ifndef FLOWENGINE_VULKANUI_H
#define FLOWENGINE_VULKANUI_H

#include "Render/UI.h"
#include <vulkan/vulkan.h>
#include "VulkanSmartHandle.h"
#include "VulkanBuffer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <GLFW/glfw3.h>
#include "Window/window.h"

namespace Flow {

    class VulkanUI : public UI{
    public:
        VulkanUI(Window* _window);
        ~VulkanUI();
        DisableCopy(VulkanUI);
    public:
        bool init() override;
        void update() override;
        void newFrame() override;
        void render() override;
        explicit operator bool() const {return anyItemActive;}
    private:
        void dockSpace();
        void updateBuffers();
        void drawFrame(VkCommandBuffer _cb);
        void initResources(VkRenderPass _renderPass, VkQueue _copyQueue, const std::string& _shadersPath);
    private:
        Window* window;
        VulkanSmartHandle<VkSampler> sampler{VK_NULL_HANDLE};
        VulkanBuffer vertexBuffer;
        VulkanBuffer indexBuffer;
        uint32_t vertexCount{};
        uint32_t indexCount{};
        VulkanSmartHandle<VkDeviceMemory> memory{VK_NULL_HANDLE};
        VulkanSmartHandle<VkImage> image{VK_NULL_HANDLE};
        VulkanSmartHandle<VkImageView> imageView{VK_NULL_HANDLE};
        VulkanSmartHandle<VkPipelineCache> pipelineCache{VK_NULL_HANDLE};
        VulkanSmartHandle<VkPipelineLayout> pipelineLayout{VK_NULL_HANDLE};
        VulkanSmartHandle<VkPipeline> pipeline{VK_NULL_HANDLE};
//        VulkanSmartHandle<VkDescriptorPool> pool{VK_NULL_HANDLE};
        VulkanSmartHandle<VkDescriptorSetLayout> setLayout{VK_NULL_HANDLE};
        VulkanSmartHandle<VkDescriptorSet> set{VK_NULL_HANDLE};
        bool anyItemActive{false};
        struct PushConstBlock {
            glm::vec2 scale;
            glm::vec2 translate;
        } pushConstBlock{};
    };
} // Flow

#endif //FLOWENGINE_VULKANUI_H
