//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_OBJECT_H
#define FLOWENGINE_OBJECT_H

#include "Scene.h"
#include "entt.hpp"
#include "Macro/Macro.h"
#include "Components.h"
#include "Transform.h"
#include <iostream>

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

        template<typename T>
        T& getComponent()
        {
            if (!componentExist<T>()) {
                FlowError(Object no such Component);
            }else {
                return scene->get().get<T>(handle);
            }
        }

        template<typename T>
        const T& getComponent() const {
            if (!componentExist<T>()) {
                FlowError(Object no such Component);
            }else {
                return scene->get().get<T>(handle);
            }
        }

        template<typename T>
        void removeComponent() {
            scene->get().remove<T>(handle);
        }

        template<typename... T>
        bool componentExist()
        {
            return scene->get().any_of<T...>(handle);
        }

        Transform& transform() {return scene->get().get<Transform>(handle);}
        glm::mat4 transform() const {return scene->get().get<Transform>(handle).getMatrix();}

        const std::string& Name() {return getComponent<Tag>();}

        operator bool () const {return handle != entt::null && scene != nullptr;}

        bool operator==(const Object& _other) const {
            return handle == _other.handle && scene == _other.scene;
        }

        bool operator!=(const Object& _other) const {
            return !(*this == _other);
        }

        void setParentID(uint64_t _parent) { getComponent<Relation>().parentHandle = _parent;}
        uint64_t getParentID() { return getComponent<Relation>().parentHandle;}
        std::vector<uint64_t>& children() { return getComponent<Relation>().children;}

        ClassProtectedReferenceElement(name, std::string, Name);
    private:
        entt::entity handle;
        Scene* scene{nullptr};
    };

} // Flow

#endif //FLOWENGINE_OBJECT_H
