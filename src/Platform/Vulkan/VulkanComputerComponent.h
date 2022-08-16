//
// Created by hasee on 2022/7/27.
//

#ifndef FLOWENGINE_VULKANCOMPUTERCOMPONENT_H
#define FLOWENGINE_VULKANCOMPUTERCOMPONENT_H

#include "Compute/ComputerComponent.h"
#include "VulkanComponent.h"
#include <vulkan/vulkan.h>

namespace Flow {

    class VulkanComputerComponent : public ComputerComponent, public VulkanComponent{
    public:
        explicit VulkanComputerComponent(std::function<void(ComputerComponent*)> _renderFunction);
        ~VulkanComputerComponent() override;
    public:
        void bindMaterial(Material* _mat) override;
        void dispatch(uint32_t _xCount, uint32_t _yCount, uint32_t _zCount) override;
    private:
        VkCommandBuffer cmb{};
    };

} // Flow

#endif //FLOWENGINE_VULKANCOMPUTERCOMPONENT_H
