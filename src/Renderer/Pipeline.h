//
// Created by hasee on 2022/7/16.
//

#ifndef FLOWENGINE_PIPELINE_H
#define FLOWENGINE_PIPELINE_H

#include "Shader.h"
#include <vector>

namespace Flow {

    class Pipeline {
    public:
        static Pipeline* GeneratePipeline(const std::vector<std::string> _files);
        virtual ~Pipeline(){};
    public:
        virtual void bind() = 0;
    private:
        std::vector<SP(Shader)> shaders;
    };

} // Flow

#endif //FLOWENGINE_PIPELINE_H
