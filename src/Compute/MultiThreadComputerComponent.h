//
// Created by hasee on 2022/11/16.
//

#ifndef FLOWENGINE_MULTITHREADCOMPUTERCOMPONENT_H
#define FLOWENGINE_MULTITHREADCOMPUTERCOMPONENT_H

#include "ComputerComponent.h"

namespace Flow {

    class MultiThreadComputerComponent : public ComputerComponent {
    public:
        explicit MultiThreadComputerComponent(std::function<void(ComputerComponent*)> _computeFunction);
        ~MultiThreadComputerComponent() override;
    public:
        void bindMaterial(Material* _mat) override;
        void dispatch(uint32_t _xCount, uint32_t _yCount, uint32_t _zCount) override;
    };

}

#endif //FLOWENGINE_MULTITHREADCOMPUTERCOMPONENT_H
