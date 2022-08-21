//
// Created by hasee on 2022/7/16.
//

#include "VulkanMaterial.h"
#include "VulkanTool.h"

namespace Flow {

    void VulkanImageMaterialUnit::bindFile(const std::string &_filename, uint32_t _resourceType) {
        auto imageType = (MaterialImageType)_resourceType;
        switch (imageType) {
            case MaterialImageType::Dimension1:
            {
                tool::reflect2DTexture(_filename, this);
                break;
            }
            case MaterialImageType::Dimension2:
            {
                tool::reflect2DTexture(_filename, this);
                break;
            }
            case MaterialImageType::Dimension3:
            {
                tool::reflect2DTexture(_filename, this);
                break;
            }
        }
    }

    VulkanMaterial::VulkanMaterial(const std::vector<std::pair<std::string, uint32_t>>& _shaderFiles) {
        for (const auto &item: _shaderFiles) {
            auto shader = Shader::createShader(item.first, item.first, item.second);
            shader->reflectMaterial(*this);
            shaders.emplace_back(shader);
        }
    }
} // Flow