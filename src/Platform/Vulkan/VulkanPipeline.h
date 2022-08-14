//
// Created by hasee on 2022/8/14.
//

#ifndef FLOWENGINE_VULKANPIPELINE_H
#define FLOWENGINE_VULKANPIPELINE_H

#include "Renderer/Pipeline.h"
#include "VulkanSmartHandle.h"

namespace Flow {

    class VulkanPipeline : public Pipeline{
    public:
        explicit VulkanPipeline(const std::vector<std::string> _files);
        ~VulkanPipeline() override;
    public:
        void bind() override {

        };
        VkPipelineLayout getLayout() const {return layout;};

    private:
        VulkanSmartHandle<VkPipelineLayout> layout{VK_NULL_HANDLE};
    };

} // Flow

#endif //FLOWENGINE_VULKANPIPELINE_H
