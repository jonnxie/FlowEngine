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
    using ObjectMap = std::unordered_map<uint64_t, Object*>;

    class Scene {
    public:
        Object createObject(const std::string& _name = "Empty Object");
        entt::registry& get(){return registry;};
        uint64_t getSceneID() {return 0;};
        Object* getObjectWithID(uint64_t _id);

        template<typename... Components>
        auto GetAllObjectsWith()
        {
            return registry.view<Components...>();
        }
    private:
        std::vector<SP(ViewPort)> viewports;
        ObjectMap objectMap;
        entt::registry registry;
    };
} // FlowEngine

#endif //FLOWENGINE_SCENE_H
