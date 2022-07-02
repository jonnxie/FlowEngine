//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANRENDERERCONTEXT_H
#define FLOWENGINE_VULKANRENDERERCONTEXT_H

#include "Renderer/RendererContext.h"
#include "Macro/Macro.h"
#include <memory>
#include <vulkan/vulkan.h>
#include <vector>

namespace Flow{

    class VulkanFrameBuffer;

    class VulkanRendererContext : public RendererContext{
    public:
        VulkanRendererContext();
        DisableCopy(VulkanRendererContext);
    private:
        void init();
    public:
        operator const VkDevice() {return device;}
        VkPhysicalDevice getPhysicalDevice() {return physicalDevice;}
        VkPhysicalDeviceMemoryProperties getPhysicalDeviceMemoryProperties() {return physicalDeviceMemoryProperties;}
        VkFormat getSwapChainFormat() {return swapChainFormat;}
        void saveScreenshot(std::basic_string<char> _filename) override;
        VkCommandBuffer beginSingleCommandBuffer();
        void endSingleCommandBuffer(VkCommandBuffer _cmd);
    private:
        VkDevice device;
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    private:
        uint32_t currentPresentIndex;
        std::vector<UP(VulkanFrameBuffer)> frameBuffers;
        VkFormat swapChainFormat;
    };

#define VulkanDevice (*(VulkanRendererContext*)RendererContext::get().get())
#define VulkanPhysicalDevice ((VulkanRendererContext*)RendererContext::get().get())->getPhysicalDevice()
#define VulkanPhysicalDeviceMemoryProperties ((VulkanRendererContext*)RendererContext::get().get())->getPhysicalDeviceMemoryProperties()
#define VulkanSwapChainFormat ((VulkanRendererContext*)RendererContext::get().get())->getSwapChainFormat()
}

#endif //FLOWENGINE_VULKANRENDERERCONTEXT_H
