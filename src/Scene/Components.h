//
// Created by hasee on 2022/7/3.
//

#ifndef FLOWENGINE_COMPONENTS_H
#define FLOWENGINE_COMPONENTS_H

#include "IDManager.h"

namespace Flow{

    struct IDComponent{
        IDComponent(){
            id = FlowID;
        };
        ~IDComponent(){
            IDManager::get().free(id);
        }
        uint64_t id;
    };

    struct MultipleComponent{

    };
}

#endif //FLOWENGINE_COMPONENTS_H
