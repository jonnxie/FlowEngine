//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_SCENE_H
#define FLOWENGINE_SCENE_H

#include "Renderer/ViewPort.h"
#include "Macro/Macro.h"
#include "entt.hpp"

namespace Flow {

    class Object;

    class Scene {
    public:
        Object createObject(const std::string& _name = "Empty Object");
        entt::registry& get(){return registry;};
    private:
        std::vector<SP(ViewPort)> viewports;
        entt::registry registry;
    };

} // FlowEngine

#endif //FLOWENGINE_SCENE_H
