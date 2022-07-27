//
// Created by hasee on 2022/7/27.
//

#ifndef FLOWENGINE_VULKANCOMPONENT_H
#define FLOWENGINE_VULKANCOMPONENT_H

#include <cstdint>
#include <vulkan/vulkan.h>

namespace Flow {

    enum class ComponentType{
        Render,
        Compute,
    };

    class VulkanComponent {
    public:
        void bindThread(uint32_t _threadIndex, ComponentType _type = ComponentType::Render);

    protected:
        VkCommandBuffer cmb{};
    };

} // Flow

#endif //FLOWENGINE_VULKANCOMPONENT_H
