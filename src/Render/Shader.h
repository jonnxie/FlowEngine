//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_SHADER_H
#define FLOWENGINE_SHADER_H

#include "Macro/Macro.h"
#include <memory>
#include <unordered_map>

namespace Flow {

    class Material;
    class Pipeline;

    class Shader {
    public:
        Shader() = default;
        virtual ~Shader() {};
    public:
        static SP(Shader) createShader(const std::string& _id, const std::string& _filename, uint32_t _type);
        typedef std::unordered_map<std::string, SP(Shader)> Registry;
        static Registry& getRegistry()
        {
            static Registry registry;
            return registry;
        }
    public:
        virtual void reflectMaterial(Material& material) const = 0;
        virtual void reflectPipeline(Pipeline& pipeline) const = 0;
    };

} // Material

#endif //FLOWENGINE_SHADER_H
