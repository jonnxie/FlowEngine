//
// Created by hasee on 2022/8/14.
//

#ifndef FLOWENGINE_VULKANPIPELINE_H
#define FLOWENGINE_VULKANPIPELINE_H

#include "Render/Pipeline.h"
#include "VulkanSmartHandle.h"

namespace Flow {

    class VulkanPipeline : public Pipeline{
    public:
        explicit VulkanPipeline();
        ~VulkanPipeline() override;
    public:
        void bind() override {

        };
        VkPipelineLayout const getLayout() const {return layout;};
        VkPipeline const getPipeline() const {return pipeline;};
        operator VkPipeline() const {return pipeline;};
    private:
        VulkanSmartHandle<VkPipelineLayout> layout{VK_NULL_HANDLE};
        VulkanSmartHandle<VkPipeline> pipeline{VK_NULL_HANDLE};
    };

} // Flow

#endif //FLOWENGINE_VULKANPIPELINE_H
