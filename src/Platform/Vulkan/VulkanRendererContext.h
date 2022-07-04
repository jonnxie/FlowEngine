//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANRENDERERCONTEXT_H
#define FLOWENGINE_VULKANRENDERERCONTEXT_H


#ifndef  GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif

#include "Renderer/RendererContext.h"
#include "Macro/Macro.h"
#include <memory>
#include <vulkan/vulkan.h>
#include <vector>



#ifdef NDEBUG
static const bool enableValidationLayers = false;
#else
static const bool enableValidationLayers = true;
#endif

namespace Flow{

    class VulkanFrameBuffer;

    const std::vector<const char *> validationLayers = {
            "VK_LAYER_RENDERDOC_Capture",
            "VK_LAYER_KHRONOS_validation",
    };

    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    class VulkanRendererContext : public RendererContext{
    public:
        VulkanRendererContext(Window* _window);
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
        void createInstance();
        void setDebugCallback();
        void createSurface();
        void createPhysicalDevice();
        void createLogicalDevice();
        void createQueueIndices();
        bool checkValidationLayerSupport();
        bool checkPhysicalDevice(VkPhysicalDevice _physicalDevice);
        bool checkExtensionSupport(VkPhysicalDevice _physicalDevice);
        bool checkQueueIndices();
        bool checkIndicesExist(int _index) const;
        std::vector<const char *> getRequiredExtensions();
        bool IsolateQueue(std::map<VkQueueFlagBits, int &> _map, const std::vector<VkQueueFamilyProperties> &_queueFamilies);
    private:
        VkDevice device;
        VkInstance instance;
        VkDebugReportCallbackEXT callback{};
        VkPhysicalDevice physicalDevice;
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
        VkSurfaceKHR surface{};
        VkPhysicalDeviceProperties physicalDeviceProperties{};
        VkQueue compute_queue;
        VkQueue graphics_queue;
        VkQueue present_queue;
        VkQueue transfer_queue;
        struct QueueFamilyIndices {
            int graphicsFamily = -1, presentFamily = -1, computeFamily = -1, transferFamily = -1;
            bool complete() const { return graphicsFamily >= 0 && presentFamily >= 0 && computeFamily >= 0 && transferFamily >= 0;}
        }queueIndices;
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
