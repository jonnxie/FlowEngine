//
// Created by hasee on 2022/7/27.
//

#ifndef FLOWENGINE_COMPUTERCOMPONENT_H
#define FLOWENGINE_COMPUTERCOMPONENT_H

#include "Macro/Macro.h"
#include <memory>
#include <functional>

namespace Flow {

    class Material;

    class ComputerComponent {
    public:
        static SP(ComputerComponent) createComputerComponent();
        virtual ~ComputerComponent() = default;
    protected:
        ComputerComponent() = default;
        explicit ComputerComponent(std::function<void(ComputerComponent*)> _computeFunction): computeFunction(std::move(_computeFunction)){};
    public:
        virtual void bindMaterial(Material* _mat) = 0;
        virtual void dispatch(uint32_t _xCount, uint32_t _yCount, uint32_t _zCount) = 0;
        void operator()(ComputerComponent* _component) {
            computeFunction(_component);
        }
    protected:
        std::function<void(ComputerComponent*)> computeFunction;
    };

} // Flow

#endif //FLOWENGINE_COMPUTERCOMPONENT_H
