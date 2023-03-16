//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_MATERIAL_H
#define FLOWENGINE_MATERIAL_H

#include <iostream>
#include <string>
#include <vector>
#include "Pipeline.h"

namespace Flow {

    enum class ResourceType{
        Texture,
        Buffer,
        Undefine,
    };

    struct MaterialUnit{
        std::string name;
        ResourceType type;
    };

    struct MaterialSet{
        std::vector<UP(MaterialUnit)> units;
    };

    class Material {
    public:
        static SP(Material) creatMaterial(const std::vector<std::pair<std::string, uint32_t>>& _shaderFiles);
        Material();
    public:
        void pushSet(UP(MaterialSet) _set) {
            sets.push_back(std::move(_set));
        }
        const std::vector<UP(MaterialSet)>& getCSets() const {return sets;}
        std::vector<UP(MaterialSet)>& getSets() {return sets;}
        const Pipeline* getPipeline() const {return  pipeline.get();}
    protected:
        std::vector<UP(MaterialSet)> sets;
        UP(Pipeline) pipeline;
    };

} // Flow

#endif //FLOWENGINE_MATERIAL_H
