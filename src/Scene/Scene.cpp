//
// Created by hasee on 2022/6/29.
//

#include "Scene.h"

#include <utility>
#include "Object.h"

namespace Flow {
    Object Scene::createObject(const std::string& _name) {
        return Object{registry.create(), this};
    }

    Object *Scene::getObjectWithID(uint64_t _id) {
        return objectMap[_id];
    }

    void Scene::addViewPort(const std::string& _id, SP(ViewPort) _viewport) {
        viewports[_id] = std::move(_viewport);
    }

    UP(Scene) makeScene(){
        return std::make_unique<Scene>();
    }
} // FlowEngine