//
// Created by hasee on 2022/7/16.
//

#ifndef FLOWENGINE_PIPELINE_H
#define FLOWENGINE_PIPELINE_H

#include "Shader.h"
#include <utility>
#include <vector>

namespace Flow {

    class Pipeline {
    public:
        static UP(Pipeline) GeneratePipeline();
        virtual ~Pipeline()= default;;
    protected:
        explicit Pipeline() = default;
    public:
        virtual void bind() = 0;
    public:
        std::vector<SP(Shader)>& getShaders() {return shaders;};
    private:
        std::vector<SP(Shader)> shaders;
    };

} // Flow

#endif //FLOWENGINE_PIPELINE_H
