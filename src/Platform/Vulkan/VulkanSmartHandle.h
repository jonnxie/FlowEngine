//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANSMARTHANDLE_H
#define FLOWENGINE_VULKANSMARTHANDLE_H

#include <functional>
#include "Macro/Macro.h"
#include <vulkan/vulkan.h>
#include "VulkanRendererContext.h"

namespace Flow {

    template<typename Handle>
    class VulkanSmartHandle {
    public:
        DisableCopy(VulkanSmartHandle);
        explicit VulkanSmartHandle(Handle _handle): handle(_handle){}
        ~VulkanSmartHandle();
        void release();
    public:
        operator Handle() const {return handle;}
        operator Handle&() {return handle;}
        Handle& operator()() {return handle;}
        VulkanSmartHandle& operator=(Handle _handle) {handle = _handle; return *this;}
    private:
        Handle handle{VK_NULL_HANDLE};
    };

    template<typename Handle>
    VulkanSmartHandle<Handle>::~VulkanSmartHandle() {
        release();
    }

    template<typename Handle>
    void VulkanSmartHandle<Handle>::release() {
        if (handle == VK_NULL_HANDLE) return;

        VkDevice device = VulkanDevice;
        if constexpr(std::is_same_v<Handle, VkBuffer>) {
            vkDestroyBuffer(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkDeviceMemory>) {
            vkFreeMemory(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkImageView>) {
            vkDestroyImageView(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkImage>) {
            vkDestroyImage(device, handle,nullptr);
        } else if constexpr(std::is_same_v<Handle, VkSampler>) {
            vkDestroySampler(device, handle,nullptr);
        } else if constexpr(std::is_same_v<Handle, VkFramebuffer>) {
            vkDestroyFramebuffer(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkPipelineCache>) {
            vkDestroyPipelineCache(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkPipelineLayout>) {
            vkDestroyPipelineLayout(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkDescriptorSetLayout>) {
            vkDestroyDescriptorSetLayout(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkPipeline>) {
            vkDestroyPipeline(device, handle, nullptr);
        } else if constexpr(std::is_same_v<Handle, VkDescriptorPool>) {
            vkDestroyDescriptorPool(device, handle, nullptr);
        }
        handle = VK_NULL_HANDLE;
    }

} // Flow

#endif //FLOWENGINE_VULKANSMARTHANDLE_H
