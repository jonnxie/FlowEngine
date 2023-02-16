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

    void Scene::addViewPort(std::shared_ptr<ViewPort> _viewport) {
        viewports.emplace_back(_viewport);
    }

    UP(Scene) makeScene(){
        return std::make_unique<Scene>();
    }
} // FlowEngine