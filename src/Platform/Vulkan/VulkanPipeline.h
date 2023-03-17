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
        VkPipelineLayout getLayout() const {return layout;};
        void generateLayout();
        VkPipeline getPipeline() const {return pipeline;};
        void setPipeline(VkPipeline _pipeline) {pipeline = _pipeline;}
        operator VkPipeline() const {return pipeline;};
    private:
        VulkanSmartHandle<VkPipelineLayout> layout{VK_NULL_HANDLE};
        VulkanSmartHandle<VkPipeline> pipeline{VK_NULL_HANDLE};
    };

} // Flow

#endif //FLOWENGINE_VULKANPIPELINE_H
