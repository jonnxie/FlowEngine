//
// Created by hasee on 2022/8/14.
//

#include "VulkanPipeline.h"
#include "VulkanShader.h"
#include "VulkanMacro.h"

namespace Flow {
    VulkanPipeline::VulkanPipeline()
    {

    }

    VulkanPipeline::~VulkanPipeline() {

    }

    void VulkanPipeline::generateLayout() {
        /*PipelineLayoutCreateInfo*/
        std::vector<VkDescriptorSetLayout> layouts;
        for (auto& shader : shaders) {
            layouts.insert(layouts.end(), static_cast<VulkanShader*>(shader.get())->getSetLayouts().begin(), static_cast<VulkanShader*>(shader.get())->getSetLayouts().end());
        }
        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
                VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                nullptr,
                0,
                uint32_t(layouts.size()),
                layouts.data(),
                0,
                nullptr};
        VkPipelineLayout layout;
        VKExecute(vkCreatePipelineLayout(VulkanDevice,
                                         &pipelineLayoutInfo,
                                         nullptr,
                                         &layout));
    }
} // Flow