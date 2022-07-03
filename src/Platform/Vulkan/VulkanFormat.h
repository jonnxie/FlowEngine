//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_VULKANFORMAT_H
#define FLOWENGINE_VULKANFORMAT_H

#include <vulkan/vulkan.h>
#include "Renderer/FrameBuffer.h"

namespace Flow{

    VkFormat generateFormat(TextureFormat _format){
        switch (_format) {
            case TextureFormat::RGBA8U:
            {
                return VK_FORMAT_R8G8B8A8_UNORM;
            }
            case TextureFormat::DEPTH24STENCIL8:
            {
                return VK_FORMAT_D24_UNORM_S8_UINT;
            }
            default:{
                return VkFormat{};
            }
        }
    };

    VkImageUsageFlags getUsage(Usage _usage)
    {
        switch (_usage) {
            case Usage::Color: {
                return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
                break;
            }
            case Usage::Depth: {
                return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
                break;
            }
            default:{
                break;
            }
        }
        return VkImageUsageFlags{};
    }
}


#endif //FLOWENGINE_VULKANFORMAT_H
