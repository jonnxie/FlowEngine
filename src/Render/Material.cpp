//
// Created by hasee on 2022/7/2.
//

#include "Material.h"
#include "Platform/Vulkan/VulkanMaterial.h"

namespace Flow {
    Material::Material() {

    }

    SP(Material) Material::creatMaterial(const std::vector<std::pair<std::string, uint32_t>>& _shaderFiles) {
        #ifdef FLOW_GRAPHICS_VULKAN
        return std::make_shared<VulkanMaterial>(_shaderFiles);
        #endif
    }
} // Flow