//
// Created by hasee on 2022/7/20.
//

#ifndef FLOWENGINE_MULTITHREADCOMPUTER_H
#define FLOWENGINE_MULTITHREADCOMPUTER_H

#include "Computer.h"

namespace Flow {
    class Scene;

    class MultiThreadComputer : public Computer{
    public:
        void compute(Scene* scene) override;
    };

} // Flow

#endif //FLOWENGINE_MULTITHREADCOMPUTER_H
