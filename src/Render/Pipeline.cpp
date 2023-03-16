//
// Created by hasee on 2022/7/16.
//

#include "Pipeline.h"
#include "Platform/Vulkan/VulkanPipeline.h"

namespace Flow {
    UP(Pipeline) Pipeline::GeneratePipeline() {
        #ifdef FLOW_GRAPHICS_VULKAN
            return std::make_unique<VulkanPipeline>();
        #endif
    }
} // Flow