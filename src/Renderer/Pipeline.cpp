//
// Created by hasee on 2022/7/16.
//

#include "Pipeline.h"
#include "Platform/Vulkan/VulkanPipeline.h"

namespace Flow {
    Pipeline *Pipeline::GeneratePipeline(const std::vector<std::string> _files) {
        #ifdef FLOW_GRAPHICS_VULKAN
            return new VulkanPipeline(_files);
        #endif
    }
} // Flow