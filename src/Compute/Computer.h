//
// Created by hasee on 2022/7/20.
//

#ifndef FLOWENGINE_COMPUTER_H
#define FLOWENGINE_COMPUTER_H

#include "Macro/Macro.h"

namespace Flow {

    class Scene;
    class ThreadPool;

    enum class ComputeMode{
        MultiThread,
        VulkanSync
    };

    class Computer {
    public:
        virtual ~Computer() = default;
        virtual void compute(Scene* scene) = 0;
    public:
        void setRenderMode(ComputeMode _mode) { computeMode = _mode;}
    protected:
        void createThreadPool();
    protected:
        ComputeMode computeMode{};
        UP(ThreadPool) threadPool;
    };

    SP(Computer) createMultipleComputer();

    SP(Computer) createVulkanComputer();

} // Flow

#endif //FLOWENGINE_COMPUTER_H
