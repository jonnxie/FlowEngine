//
// Created by hasee on 2022/7/20.
//

#ifndef FLOWENGINE_VULKANCOMPUTER_H
#define FLOWENGINE_VULKANCOMPUTER_H

#include <vulkan/vulkan.h>
#include "Compute/Computer.h"

namespace Flow {

    class VulkanComputer : public Computer{
    public:
        ~VulkanComputer();
    public:
        void compute(Scene* scene) override;
    private:
        void init();
        void createComputeCB();
    private:
        VkCommandBuffer computeCB;
    };

} // Flow

#endif //FLOWENGINE_VULKANCOMPUTER_H
