//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANRENDERERCONTEXT_H
#define FLOWENGINE_VULKANRENDERERCONTEXT_H


#ifndef  GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif

#include "Render/RendererContext.h"
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

    class VulkanRenderer;

    class VulkanComputer;

    const std::vector<const char *> validationLayers = {
            "VK_LAYER_RENDERDOC_Capture",
            "VK_LAYER_KHRONOS_validation",
    };

    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats{};
        std::vector<VkPresentModeKHR> presentModes{};
    };

    enum class QueueType{
        Graphics,
        Compute,
        Present,
        Transfer
    };

    enum class CBType{
        Graphics,
        Compute,
        Transfer,
    };

    struct QueueFamilyIndices {
        int graphicsFamily = -1, presentFamily = -1, computeFamily = -1, transferFamily = -1;
        bool complete() const { return graphicsFamily >= 0 && presentFamily >= 0 && computeFamily >= 0 && transferFamily >= 0;}
    };

    class VulkanRendererContext : public RendererContext{
    public:
        VulkanRendererContext(Window* _window);
        DisableCopy(VulkanRendererContext);
        ~VulkanRendererContext() override;
    private:
        void init();
    public:
        operator const VkDevice() {return device;}
        VkDevice& getLogicalDevice() {return device;}
        VkPhysicalDevice getPhysicalDevice() {return physicalDevice;}
        VkPhysicalDeviceMemoryProperties getPhysicalDeviceMemoryProperties() {return physicalDeviceMemoryProperties;}
        VkFormat getSwapChainFormat() {return swapChainFormat;}
        void saveScreenshot(std::basic_string<char> _filename) override;
        VkCommandBuffer beginSingleCommandBuffer(CBType _type = CBType::Graphics);
        VkRenderPass getPresentRenderPass() {return presentRenderPass;}
        void endSingleCommandBuffer(VkCommandBuffer _cmd, CBType _type = CBType::Graphics);
        VkQueue getQueue(QueueType _type);
        VkCommandPool getCBPool(CBType _type);
        VkInstance getInstance() {return instance;};
        QueueFamilyIndices& getIndices() {return queueIndices;}
        VkDescriptorPool& getDescriptorPool() {return descriptorPool;}
        VkSampler& getLinearSampler() {return linearSampler;}
        uint32_t getSwapChainCount() const {return swapchainCount;}
        uint32_t getMinSwapChainCount() const {return minSwapchainCount;}
        void allocateDescriptorSet(VkDescriptorSetLayout _setLayout, VkDescriptorSet* _set);
        VulkanRenderer* getRenderer() {return renderer;}
        void setRenderer(VulkanRenderer* _renderer) { renderer = _renderer;}
        VulkanComputer* getComputer() {return computer;}
        void setComputer(VulkanComputer* _computer) { computer = _computer;}
        VkCommandPool getGraphicsCMDPool() const {return graphicCP;}
        VkCommandPool getComputeCMDPool() const {return computeCP;}
        VkCommandPool getTransferCMDPool() const {return transferCP;}
    private:
        void createInstance();
        void setDebugCallback();
        void createSurface();
        void createPhysicalDevice();
        void createLogicalDevice();
        void createQueueIndices();
        void createSwapChain();
        void createPresentRenderPass();
        void createCommandPool();
        void createGraphicsCommandPool();
        void createComputeCommandPool();
        void createTransferCommandPool();
        void createDescriptorPool();
        void createPresentFrameBuffers();
        void createLinearSampler();
        void createSemaphores();
        bool checkPhysicalDevice(VkPhysicalDevice _physicalDevice);
        bool checkValidationLayerSupport();
        bool checkExtensionSupport(VkPhysicalDevice _physicalDevice);
        bool checkQueueIndices();
        bool checkIndicesExist(int _index) const;
        SwapChainSupportDetails checkSwapChainSupport();
        std::vector<const char *> getRequiredExtensions();
        bool IsolateQueue(std::map<VkQueueFlagBits, int &> _map, const std::vector<VkQueueFamilyProperties> &_queueFamilies);
    private:
        VkDevice device{};
        VkInstance instance{};
        VkDebugReportCallbackEXT callback{};
        VkPhysicalDevice physicalDevice{};
        std::string physicalDeviceName{};
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
        VkSurfaceKHR surface{};
        VkPhysicalDeviceProperties physicalDeviceProperties{};
        VkQueue computeQueue{}, graphicsQueue{}, presentQueue{}, transferQueue{};
        VkCommandPool graphicCP{}, computeCP{}, transferCP{};
        VkDescriptorPool descriptorPool{};
        VkSampler linearSampler{};
        QueueFamilyIndices queueIndices{};
    private:
        uint32_t currentPresentIndex{};
        VkFormat swapChainFormat{};
        VkSwapchainKHR swapchain{VK_NULL_HANDLE};
        uint32_t swapchainCount{};
        uint32_t minSwapchainCount{};
        VkRenderPass presentRenderPass{};
        VkSemaphore imageAvailableSemaphore;
        struct VkPresent {
            VkImage image;
            VkImageView imageView;
            VkSampler sampler;
            VkFramebuffer framebuffer;
        };
        std::vector<VkPresent> m_presents{};
        VulkanRenderer* renderer;
        VulkanComputer* computer;
    };

#define VulkanDevice ((VulkanRendererContext*)RendererContext::get().get())->getLogicalDevice()
#define VulkanGraphicsCMDPool ((VulkanRendererContext*)RendererContext::get().get())->getGraphicsCMDPool()
#define VulkanComputeCMDPool ((VulkanRendererContext*)RendererContext::get().get())->getComputeCMDPool()
#define VulkanTransferCMDPool ((VulkanRendererContext*)RendererContext::get().get())->getTransferCMDPool()
#define VulkanPhysicalDevice ((VulkanRendererContext*)RendererContext::get().get())->getPhysicalDevice()
#define VulkanPhysicalDeviceMemoryProperties ((VulkanRendererContext*)RendererContext::get().get())->getPhysicalDeviceMemoryProperties()
#define VulkanSwapChainFormat ((VulkanRendererContext*)RendererContext::get().get())->getSwapChainFormat()
#define VulkanDescriptorPool ((VulkanRendererContext*)RendererContext::get().get())->getDescriptorPool()
#define VulkanContext ((VulkanRendererContext*)RendererContext::get().get())
#define VulkanSampler ((VulkanRendererContext*)RendererContext::get().get())->getLinearSampler()
}

#endif //FLOWENGINE_VULKANRENDERERCONTEXT_H
