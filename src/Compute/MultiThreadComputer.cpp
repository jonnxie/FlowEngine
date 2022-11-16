//
// Created by hasee on 2022/7/20.
//

#include "MultiThreadComputer.h"
#include "Scene/Scene.h"
#include "Scene/Object.h"
#include "MultiThreadComputerComponent.h"
#include "threadpool.h"

namespace Flow {
    void MultiThreadComputer::compute(Scene *scene) {
        auto view = scene->GetAllObjectsWith<MultiThreadComputerComponent>();
        std::vector<MultiThreadComputerComponent*> components{};
        for (auto& entityID : view)
        {
            Object Object = { entityID, scene };
            components.push_back(&Object.getComponent<MultiThreadComputerComponent>());
        }
        threadPool->executeVector<MultiThreadComputerComponent*>(components, [](MultiThreadComputerComponent* _item,size_t _index, size_t _threadIndex){
            (*_item)(_item);
        });
    }
} // Flow