//
// Created by hasee on 2022/7/16.
//

#include "VulkanShader.h"
#include <vulkan/vulkan.h>
#include "Macro/Macro.h"
#include "VulkanTool.h"
#include "VulkanRendererContext.h"
#include "VulkanMaterial.h"

namespace Flow {

    static uint32_t FormatSize(VkFormat format)
    {
        uint32_t result = 0;
        switch (format) {
            case VK_FORMAT_UNDEFINED: result = 0; break;
            case VK_FORMAT_R4G4_UNORM_PACK8: result = 1; break;
            case VK_FORMAT_R4G4B4A4_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_B4G4R4A4_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_R5G6B5_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_B5G6R5_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_R5G5B5A1_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_B5G5R5A1_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_A1R5G5B5_UNORM_PACK16: result = 2; break;
            case VK_FORMAT_R8_UNORM: result = 1; break;
            case VK_FORMAT_R8_SNORM: result = 1; break;
            case VK_FORMAT_R8_USCALED: result = 1; break;
            case VK_FORMAT_R8_SSCALED: result = 1; break;
            case VK_FORMAT_R8_UINT: result = 1; break;
            case VK_FORMAT_R8_SINT: result = 1; break;
            case VK_FORMAT_R8_SRGB: result = 1; break;
            case VK_FORMAT_R8G8_UNORM: result = 2; break;
            case VK_FORMAT_R8G8_SNORM: result = 2; break;
            case VK_FORMAT_R8G8_USCALED: result = 2; break;
            case VK_FORMAT_R8G8_SSCALED: result = 2; break;
            case VK_FORMAT_R8G8_UINT: result = 2; break;
            case VK_FORMAT_R8G8_SINT: result = 2; break;
            case VK_FORMAT_R8G8_SRGB: result = 2; break;
            case VK_FORMAT_R8G8B8_UNORM: result = 3; break;
            case VK_FORMAT_R8G8B8_SNORM: result = 3; break;
            case VK_FORMAT_R8G8B8_USCALED: result = 3; break;
            case VK_FORMAT_R8G8B8_SSCALED: result = 3; break;
            case VK_FORMAT_R8G8B8_UINT: result = 3; break;
            case VK_FORMAT_R8G8B8_SINT: result = 3; break;
            case VK_FORMAT_R8G8B8_SRGB: result = 3; break;
            case VK_FORMAT_B8G8R8_UNORM: result = 3; break;
            case VK_FORMAT_B8G8R8_SNORM: result = 3; break;
            case VK_FORMAT_B8G8R8_USCALED: result = 3; break;
            case VK_FORMAT_B8G8R8_SSCALED: result = 3; break;
            case VK_FORMAT_B8G8R8_UINT: result = 3; break;
            case VK_FORMAT_B8G8R8_SINT: result = 3; break;
            case VK_FORMAT_B8G8R8_SRGB: result = 3; break;
            case VK_FORMAT_R8G8B8A8_UNORM: result = 4; break;
            case VK_FORMAT_R8G8B8A8_SNORM: result = 4; break;
            case VK_FORMAT_R8G8B8A8_USCALED: result = 4; break;
            case VK_FORMAT_R8G8B8A8_SSCALED: result = 4; break;
            case VK_FORMAT_R8G8B8A8_UINT: result = 4; break;
            case VK_FORMAT_R8G8B8A8_SINT: result = 4; break;
            case VK_FORMAT_R8G8B8A8_SRGB: result = 4; break;
            case VK_FORMAT_B8G8R8A8_UNORM: result = 4; break;
            case VK_FORMAT_B8G8R8A8_SNORM: result = 4; break;
            case VK_FORMAT_B8G8R8A8_USCALED: result = 4; break;
            case VK_FORMAT_B8G8R8A8_SSCALED: result = 4; break;
            case VK_FORMAT_B8G8R8A8_UINT: result = 4; break;
            case VK_FORMAT_B8G8R8A8_SINT: result = 4; break;
            case VK_FORMAT_B8G8R8A8_SRGB: result = 4; break;
            case VK_FORMAT_A8B8G8R8_UNORM_PACK32: result = 4; break;
            case VK_FORMAT_A8B8G8R8_SNORM_PACK32: result = 4; break;
            case VK_FORMAT_A8B8G8R8_USCALED_PACK32: result = 4; break;
            case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: result = 4; break;
            case VK_FORMAT_A8B8G8R8_UINT_PACK32: result = 4; break;
            case VK_FORMAT_A8B8G8R8_SINT_PACK32: result = 4; break;
            case VK_FORMAT_A8B8G8R8_SRGB_PACK32: result = 4; break;
            case VK_FORMAT_A2R10G10B10_UNORM_PACK32: result = 4; break;
            case VK_FORMAT_A2R10G10B10_SNORM_PACK32: result = 4; break;
            case VK_FORMAT_A2R10G10B10_USCALED_PACK32: result = 4; break;
            case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: result = 4; break;
            case VK_FORMAT_A2R10G10B10_UINT_PACK32: result = 4; break;
            case VK_FORMAT_A2R10G10B10_SINT_PACK32: result = 4; break;
            case VK_FORMAT_A2B10G10R10_UNORM_PACK32: result = 4; break;
            case VK_FORMAT_A2B10G10R10_SNORM_PACK32: result = 4; break;
            case VK_FORMAT_A2B10G10R10_USCALED_PACK32: result = 4; break;
            case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: result = 4; break;
            case VK_FORMAT_A2B10G10R10_UINT_PACK32: result = 4; break;
            case VK_FORMAT_A2B10G10R10_SINT_PACK32: result = 4; break;
            case VK_FORMAT_R16_UNORM: result = 2; break;
            case VK_FORMAT_R16_SNORM: result = 2; break;
            case VK_FORMAT_R16_USCALED: result = 2; break;
            case VK_FORMAT_R16_SSCALED: result = 2; break;
            case VK_FORMAT_R16_UINT: result = 2; break;
            case VK_FORMAT_R16_SINT: result = 2; break;
            case VK_FORMAT_R16_SFLOAT: result = 2; break;
            case VK_FORMAT_R16G16_UNORM: result = 4; break;
            case VK_FORMAT_R16G16_SNORM: result = 4; break;
            case VK_FORMAT_R16G16_USCALED: result = 4; break;
            case VK_FORMAT_R16G16_SSCALED: result = 4; break;
            case VK_FORMAT_R16G16_UINT: result = 4; break;
            case VK_FORMAT_R16G16_SINT: result = 4; break;
            case VK_FORMAT_R16G16_SFLOAT: result = 4; break;
            case VK_FORMAT_R16G16B16_UNORM: result = 6; break;
            case VK_FORMAT_R16G16B16_SNORM: result = 6; break;
            case VK_FORMAT_R16G16B16_USCALED: result = 6; break;
            case VK_FORMAT_R16G16B16_SSCALED: result = 6; break;
            case VK_FORMAT_R16G16B16_UINT: result = 6; break;
            case VK_FORMAT_R16G16B16_SINT: result = 6; break;
            case VK_FORMAT_R16G16B16_SFLOAT: result = 6; break;
            case VK_FORMAT_R16G16B16A16_UNORM: result = 8; break;
            case VK_FORMAT_R16G16B16A16_SNORM: result = 8; break;
            case VK_FORMAT_R16G16B16A16_USCALED: result = 8; break;
            case VK_FORMAT_R16G16B16A16_SSCALED: result = 8; break;
            case VK_FORMAT_R16G16B16A16_UINT: result = 8; break;
            case VK_FORMAT_R16G16B16A16_SINT: result = 8; break;
            case VK_FORMAT_R16G16B16A16_SFLOAT: result = 8; break;
            case VK_FORMAT_R32_UINT: result = 4; break;
            case VK_FORMAT_R32_SINT: result = 4; break;
            case VK_FORMAT_R32_SFLOAT: result = 4; break;
            case VK_FORMAT_R32G32_UINT: result = 8; break;
            case VK_FORMAT_R32G32_SINT: result = 8; break;
            case VK_FORMAT_R32G32_SFLOAT: result = 8; break;
            case VK_FORMAT_R32G32B32_UINT: result = 12; break;
            case VK_FORMAT_R32G32B32_SINT: result = 12; break;
            case VK_FORMAT_R32G32B32_SFLOAT: result = 12; break;
            case VK_FORMAT_R32G32B32A32_UINT: result = 16; break;
            case VK_FORMAT_R32G32B32A32_SINT: result = 16; break;
            case VK_FORMAT_R32G32B32A32_SFLOAT: result = 16; break;
            case VK_FORMAT_R64_UINT: result = 8; break;
            case VK_FORMAT_R64_SINT: result = 8; break;
            case VK_FORMAT_R64_SFLOAT: result = 8; break;
            case VK_FORMAT_R64G64_UINT: result = 16; break;
            case VK_FORMAT_R64G64_SINT: result = 16; break;
            case VK_FORMAT_R64G64_SFLOAT: result = 16; break;
            case VK_FORMAT_R64G64B64_UINT: result = 24; break;
            case VK_FORMAT_R64G64B64_SINT: result = 24; break;
            case VK_FORMAT_R64G64B64_SFLOAT: result = 24; break;
            case VK_FORMAT_R64G64B64A64_UINT: result = 32; break;
            case VK_FORMAT_R64G64B64A64_SINT: result = 32; break;
            case VK_FORMAT_R64G64B64A64_SFLOAT: result = 32; break;
            case VK_FORMAT_B10G11R11_UFLOAT_PACK32: result = 4; break;
            case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: result = 4; break;
            default:
                break;
        }
        return result;
    }

    struct DescriptorSetLayoutData {
        uint32_t set_number;
        VkDescriptorSetLayoutCreateInfo create_info;
        std::vector<VkDescriptorSetLayoutBinding> bindings;
    };

    VulkanShader::VulkanShader(const std::string &_filename, uint32_t _type) : Shader(){
        if(!file::fileExists(_filename)){
            throwFile(_filename);
        }
        auto shader_code = file::readFile(_filename);
        shaderInfo.pNext = VK_NULL_HANDLE;
        shaderInfo.flags = 0;
        shaderInfo.pSpecializationInfo = VK_NULL_HANDLE;
        auto m_shader_module = tool::createShaderModule(shader_code, VulkanDevice);

        {
            SpvReflectResult result = spvReflectCreateShaderModule(shader_code.size(), shader_code.data(), &module);
            assert(result == SPV_REFLECT_RESULT_SUCCESS);

            /*
             * Generate Vertex Input Layout Create Info.
             */
            if (_type == VertexShader)
            {
                uint32_t count = 0;
                result = spvReflectEnumerateInputVariables(&module, &count, NULL);
                assert(result == SPV_REFLECT_RESULT_SUCCESS);

                std::vector<SpvReflectInterfaceVariable*> input_vars(count);
                result = spvReflectEnumerateInputVariables(&module, &count, input_vars.data());
                assert(result == SPV_REFLECT_RESULT_SUCCESS);
                if (module.shader_stage == SPV_REFLECT_SHADER_STAGE_VERTEX_BIT) {
                    // Demonstrates how to generate all necessary data structures to populate
                    // a VkPipelineVertexInputStateCreateInfo structure, given the module's
                    // expected input variables.
                    //
                    // Simplifying assumptions:
                    // - All vertex input attributes are sourced from a single vertex buffer,
                    //   bound to VB slot 0.
                    // - Each vertex's attribute are laid out in ascending order by location.
                    // - The format of each attribute matches its usage in the shader;
                    //   float4 -> VK_FORMAT_R32G32B32A32_FLOAT, etc. No attribute compression is applied.
                    // - All attributes are provided per-vertex, not per-instance.
                    VkVertexInputBindingDescription binding_description = {};
                    binding_description.binding = 0;
                    binding_description.stride = 0;  // computed below
                    binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
                    VkPipelineVertexInputStateCreateInfo vertex_input_state_create_info = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
                    std::vector<VkVertexInputAttributeDescription> attribute_descriptions;
                    attribute_descriptions.reserve(input_vars.size());
                    for (size_t i_var = 0; i_var < input_vars.size(); ++i_var) {
                        const SpvReflectInterfaceVariable& refl_var = *(input_vars[i_var]);
                        // ignore built-in variables
                        if (refl_var.decoration_flags & SPV_REFLECT_DECORATION_BUILT_IN) {
                            continue;
                        }
                        VkVertexInputAttributeDescription attr_desc{};
                        attr_desc.location = refl_var.location;
                        attr_desc.binding = binding_description.binding;
                        attr_desc.format = static_cast<VkFormat>(refl_var.format);
                        attr_desc.offset = 0;  // final offset computed below after sorting.
                        attribute_descriptions.push_back(attr_desc);
                    }
                    // Sort attributes by location
                    std::sort(std::begin(attribute_descriptions), std::end(attribute_descriptions),
                              [](const VkVertexInputAttributeDescription& a, const VkVertexInputAttributeDescription& b) {
                                  return a.location < b.location; });
                    // Compute final offsets of each attribute, and total vertex stride.
                    for (auto& attribute : attribute_descriptions) {
                        uint32_t format_size = FormatSize(attribute.format);
                        attribute.offset = binding_description.stride;
                        binding_description.stride += format_size;
                    }
                    // Nothing further is done with attribute_descriptions or binding_description
                    // in this sample. A real application would probably derive this information from its
                    // mesh format(s); a similar mechanism could be used to ensure mesh/shader compatibility.
                }
            }

            /*
             * Generate Descriptor Set Layout.
             */
            {
                uint32_t count = 0;
                result = spvReflectEnumerateDescriptorSets(&module, &count, NULL);
                assert(result == SPV_REFLECT_RESULT_SUCCESS);

                result = spvReflectEnumerateDescriptorSets(&module, &count, sets.data());
                assert(result == SPV_REFLECT_RESULT_SUCCESS);

                sets.resize(count);
                std::vector<DescriptorSetLayoutData> set_layouts(sets.size(), DescriptorSetLayoutData{});
                setLayouts.resize(count);
                VkDescriptorSetLayout vk_layout;
                for (size_t i_set = 0; i_set < sets.size(); ++i_set) {
                    const SpvReflectDescriptorSet& _set = *(sets[i_set]);
                    DescriptorSetLayoutData& layout = set_layouts[i_set];
                    layout.bindings.resize(_set.binding_count);
                    for (uint32_t i_binding = 0; i_binding < _set.binding_count; ++i_binding) {
                        const SpvReflectDescriptorBinding& refl_binding = *(_set.bindings[i_binding]);
                        VkDescriptorSetLayoutBinding& layout_binding = layout.bindings[i_binding];
                        layout_binding.binding = refl_binding.binding;
                        layout_binding.descriptorType = static_cast<VkDescriptorType>(refl_binding.descriptor_type);
                        layout_binding.descriptorCount = 1;
                        for (uint32_t i_dim = 0; i_dim < refl_binding.array.dims_count; ++i_dim) {
                            layout_binding.descriptorCount *= refl_binding.array.dims[i_dim];
                        }
                        layout_binding.stageFlags = static_cast<VkShaderStageFlagBits>(module.shader_stage);
                    }
                    layout.set_number = _set.set;
                    layout.create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
                    layout.create_info.bindingCount = _set.binding_count;
                    layout.create_info.pBindings = layout.bindings.data();

                    vkCreateDescriptorSetLayout(VulkanDevice,
                                                &layout.create_info,
                                                nullptr,
                                                &vk_layout
                    );
                    setLayouts[i_set] = vk_layout;
                }
            }
        }

        shaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        switch (_type) {
            case VertexShader:{
                shaderInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
                break;
            }
            case FragmentShader:{
                shaderInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                break;
            }
            case ComputeShader:{
                shaderInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
                break;
            }
            case RayGen:{
                shaderInfo.stage = VK_SHADER_STAGE_RAYGEN_BIT_KHR;
                break;
            }
            case RayMiss:{
                shaderInfo.stage = VK_SHADER_STAGE_MISS_BIT_KHR;
                break;
            }
            case RayClosest:{
                shaderInfo.stage = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
                break;
            }
            case TaskShader:{
                shaderInfo.stage = VK_SHADER_STAGE_TASK_BIT_NV;
                break;
            }
            case MeshShader:{
                shaderInfo.stage = VK_SHADER_STAGE_MESH_BIT_NV;
                break;
            }
            default: break;
        }
        shaderInfo.module = m_shader_module;
        shaderInfo.pName = "main";
    }

    ResourceType reflectResourceType(SpvReflectDescriptorType _descriptorType)
    {
        switch (_descriptorType) {
            case SPV_REFLECT_DESCRIPTOR_TYPE_SAMPLER:
                return ResourceType::Texture;
            case SPV_REFLECT_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
                return ResourceType::Texture;
            case SPV_REFLECT_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
                return ResourceType::Texture;
            case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_IMAGE:
                return ResourceType::Texture;
            case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
                return ResourceType::Buffer;
            case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
                return ResourceType::Buffer;
            case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
                return ResourceType::Buffer;
            case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_BUFFER:
                return ResourceType::Buffer;
            case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
                return ResourceType::Buffer;
            case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
                return ResourceType::Buffer;
            case SPV_REFLECT_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
                return ResourceType::Undefine;
            case SPV_REFLECT_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
                return ResourceType::Undefine;
        }
    }

    static UP(VulkanMaterialUnit) reflectMaterialUnit(const SpvReflectDescriptorBinding& _binding)
    {
        auto type = reflectResourceType(_binding.descriptor_type);
        uint32_t binding = _binding.binding;
        if (type == ResourceType::Buffer)
        {
            auto unit = std::make_unique<VulkanBufferMaterialUnit>();
            unit->name = _binding.name;
            unit->type = type;
            unit->memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
            unit->bufferUsageFlags = tool::reflectBufferUsage(_binding.descriptor_type);
            unit->binding = binding;
            return std::move(unit);
        } else {
            auto unit = std::make_unique<VulkanImageMaterialUnit>();
            unit->name = _binding.name;
            unit->type = type;
            unit->memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
            unit->imageUsageFlags = tool::reflectImageUsage(_binding.descriptor_type);
            unit->binding = binding;
            return std::move(unit);
        }
    }

    UP(VulkanMaterialSet) VulkanShader::reflectMaterialSet(const SpvReflectDescriptorSet& _set) const{
        auto set = std::make_unique<VulkanMaterialSet>();
        for (uint32_t i_binding = 0; i_binding < _set.binding_count; ++i_binding) {
            auto unit = reflectMaterialUnit(*(_set.bindings[i_binding]));
            unit->set = set.get();
            set->units.push_back(std::move(unit));
        }
        DescriptorSetLayoutData layout;
        layout.bindings.resize(_set.binding_count);
        for (uint32_t i_binding = 0; i_binding < _set.binding_count; ++i_binding) {
            const SpvReflectDescriptorBinding& refl_binding = *(_set.bindings[i_binding]);
            VkDescriptorSetLayoutBinding& layout_binding = layout.bindings[i_binding];
            layout_binding.binding = refl_binding.binding;
            layout_binding.descriptorType = static_cast<VkDescriptorType>(refl_binding.descriptor_type);
            layout_binding.descriptorCount = 1;
            for (uint32_t i_dim = 0; i_dim < refl_binding.array.dims_count; ++i_dim) {
                layout_binding.descriptorCount *= refl_binding.array.dims[i_dim];
            }
            layout_binding.stageFlags = static_cast<VkShaderStageFlagBits>(module.shader_stage);
        }
        layout.set_number = _set.set;
        layout.create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layout.create_info.bindingCount = _set.binding_count;
        layout.create_info.pBindings = layout.bindings.data();

        VkDescriptorSetLayout setLayout;
        vkCreateDescriptorSetLayout(VulkanDevice,
                                    &layout.create_info,
                                    nullptr,
                                    &setLayout);

        VulkanContext->allocateDescriptorSet(setLayout, &set->set);
        vkDestroyDescriptorSetLayout(VulkanDevice, setLayout, nullptr);
        return std::move(set);
    }


    void VulkanShader::reflectMaterial(Material &material) const {
        for (auto set : sets) {
            material.pushSet(reflectMaterialSet(*set));
        }
    }

    VulkanShader::~VulkanShader() {
        spvReflectDestroyShaderModule(&module);
        vkDestroyShaderModule(VulkanDevice, shaderInfo.module, nullptr);
    }
} // Flow