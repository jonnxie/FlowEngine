//
// Created by hasee on 2022/11/16.
//

#include "MultiThreadComputerComponent.h"

namespace Flow
{

    MultiThreadComputerComponent::MultiThreadComputerComponent(
            std::function<void(ComputerComponent *)> _computeFunction) : ComputerComponent(_computeFunction) {

    }

    MultiThreadComputerComponent::~MultiThreadComputerComponent() {

    }

    void MultiThreadComputerComponent::bindMaterial(Material *_mat) {

    }

    void MultiThreadComputerComponent::dispatch(uint32_t _xCount, uint32_t _yCount, uint32_t _zCount) {

    }
}


