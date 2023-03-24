//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_SCENE_H
#define FLOWENGINE_SCENE_H

#include "Render/ViewPort.h"
#include "Macro/Macro.h"
#include "entt.hpp"
#include <unordered_map>

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
    public:
        void addViewPort(const std::string& _id, SP(ViewPort) _viewport);
    private:
        std::unordered_map<std::string, SP(ViewPort)> viewports;
        ObjectMap objectMap;
        entt::registry registry;
    };

    UP(Scene) makeScene();
} // FlowEngine

#endif //FLOWENGINE_SCENE_H
