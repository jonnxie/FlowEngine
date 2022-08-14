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
        Material(const std::string _shaderFile);
    public:
        void pushSet(UP(MaterialSet) _set) {
            sets.push_back(std::move(_set));
        }
        std::vector<UP(MaterialSet)>& getSets() {return sets;}
        Pipeline* getPipeline() {return  pipeline.get();}
    private:
        std::vector<UP(MaterialSet)> sets;
        UP(Pipeline) pipeline;
    };

} // Flow

#endif //FLOWENGINE_MATERIAL_H
