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
} // Flow