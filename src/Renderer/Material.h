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
        virtual void bindFile(const std::string& _filename) = 0;
    };

    struct MaterialSet{
        std::vector<UP(MaterialUnit)> units;
    };

    class Material {
    public:
        void pushSet(UP(MaterialSet) _set) {
            sets.push_back(std::move(_set));
        }
    private:
        std::vector<UP(MaterialSet)> sets;

    };

} // Flow

#endif //FLOWENGINE_MATERIAL_H
