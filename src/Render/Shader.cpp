//
// Created by hasee on 2022/7/2.
//

#include "Shader.h"
#include <iostream>
#include "Platform/Vulkan/VulkanShader.h"

namespace Flow {
    SP(Shader) Shader::createShader(const std::string& _id, const std::string& _filename, uint32_t _type) {
        if (getRegistry().count(_id) != 0)
        {
            FlowWarning(Shader Id Is Alerady Exist);
            return getRegistry()[_id];
        }
        SP(Shader) result;
        #ifdef FLOW_GRAPHICS_VULKAN
            result = std::make_shared<VulkanShader>(_filename, _type);
        #endif
        getRegistry()[_id] = result;
        return result;
    }
} // Material