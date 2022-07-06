//
// Created by hasee on 2022/6/29.
//

#include "Scene.h"
#include "Object.h"

namespace Flow {
    Object Scene::createObject(const std::string& _name) {
        return Object{registry.create(), this};
    }

    Object *Scene::getObjectWithID(uint64_t _id) {
        return objectMap[_id];
    }
} // FlowEngine