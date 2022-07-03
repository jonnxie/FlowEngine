//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_OBJECT_H
#define FLOWENGINE_OBJECT_H

#include "Scene.h"
#include "entt.hpp"
#include "Macro/Macro.h"
#include "Components.h"

namespace Flow {

    class Object {
    public:
        Object(entt::entity _handle, Scene* _scene) : handle(_handle),scene(_scene){}
        ~Object() = default;

        template<typename T, typename... Args>
        T& addComponent(Args&&... args)
        {
            if constexpr(!std::is_convertible_v<MultipleComponent, T>)
            {
                if (componentExist<T>())
                {
                    return T{};
                };
            }
            return scene->get().emplace<T>(handle, std::forward<Args>(args)...);
        }

        template<typename... T>
        bool componentExist()
        {
            return scene->get().any_of<T...>(handle);
        }

        ClassProtectedReferenceElement(name, std::string, Name);
    private:
        entt::entity handle;
        Scene* scene{nullptr};
    };

} // Flow

#endif //FLOWENGINE_OBJECT_H
