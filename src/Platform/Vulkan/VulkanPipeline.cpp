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
            layouts.insert(layouts.end(), dynamic_cast<VulkanShader*>(shader.get())->getSetLayouts().begin(), dynamic_cast<VulkanShader*>(shader.get())->getSetLayouts().end());
        }
        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
                VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                nullptr,
                0,
                uint32_t(layouts.size()),
                layouts.data(),
                0,
                nullptr};
        VKExecute(vkCreatePipelineLayout(VulkanDevice,
                                         &pipelineLayoutInfo,
                                         nullptr,
                                         &m_layout()));
    }

    void VulkanPipeline::generateInputLayout() {

    }
} // Flow