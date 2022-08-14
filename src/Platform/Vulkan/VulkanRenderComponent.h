//
// Created by hasee on 2022/7/23.
//

#ifndef FLOWENGINE_VULKANRENDERCOMPONENT_H
#define FLOWENGINE_VULKANRENDERCOMPONENT_H

#include <vulkan/vulkan.h>
#include "Renderer/RenderComponent.h"
#include "VulkanComponent.h"

namespace Flow {

    class VulkanMaterialSet;

    class VulkanPipeline;

    class VulkanRenderComponent : public RenderComponent,public VulkanComponent{
    public:
        explicit VulkanRenderComponent(std::function<void(RenderComponent*)> _renderFunction);
        ~VulkanRenderComponent() override;
    public:
        void drawIndex(size_t _count, size_t _offset) override;
        void bindMaterial(Material* _mat) override;

    private:
        void bindMaterialSet(uint32_t _index, VulkanPipeline* _pipeline, VulkanMaterialSet* _set);
    private:
        VkCommandBuffer cmb{};
    };

} // Flow

#endif //FLOWENGINE_VULKANRENDERCOMPONENT_H
