//
// Created by hasee on 2022/7/20.
//

#ifndef FLOWENGINE_COMPUTER_H
#define FLOWENGINE_COMPUTER_H

namespace Flow {

    class Scene;

    class Computer {
        virtual void compute(Scene* scene) = 0;
    };

} // Flow

#endif //FLOWENGINE_COMPUTER_H
