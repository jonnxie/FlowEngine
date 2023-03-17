//
// Created by hasee on 2022/7/16.
//

#ifndef FLOWENGINE_VULKANSHADER_H
#define FLOWENGINE_VULKANSHADER_H

#include <vulkan/vulkan.h>
#include "Render/Shader.h"
#include <vector>
#include "spirv_reflect.h"
#include "VulkanMaterial.h"

namespace Flow {

    class VulkanShader : public Shader{
    public:
        VulkanShader(const std::string& _filename, uint32_t _type);
        ~VulkanShader() override;
    public:
        void reflectMaterial(Material& material) const override;
        void reflectPipeline(Pipeline& pipeline) const override;
        const VkPipelineShaderStageCreateInfo& getInfo() { return shaderInfo;};
        const std::vector<VkDescriptorSetLayout>& getSetLayouts() const {return setLayouts;}
    private:
        UP(VulkanMaterialSet) reflectMaterialSet(const SpvReflectDescriptorSet& _set) const;
    private:
        std::vector<VkDescriptorSetLayout> setLayouts{};
        VkPipelineShaderStageCreateInfo shaderInfo{};
        SpvReflectShaderModule module = {};
        std::vector<SpvReflectDescriptorSet*> sets{};
    };

} // Flow

#endif //FLOWENGINE_VULKANSHADER_H
