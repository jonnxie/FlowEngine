//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_RENDERER_H
#define FLOWENGINE_RENDERER_H

#include <vector>
#include "Macro/Macro.h"
#include "Engine.h"

#include <memory>
namespace Flow {

class FrameBuffer;
class Scene;

    enum class RenderMode{
        SingleThread,
        MultiThread
    };

    class Renderer {
    public:
        static SP(Renderer) createRender();
        virtual ~Renderer() = default;
    public:
        virtual void render(Scene* scene) = 0;
        virtual void attachFrameBuffer(FrameBuffer* frameBuffer) = 0;
    public:
        void setRenderMode(RenderMode _mode) { renderMode = _mode;}
    protected:
        RenderMode renderMode{};
    };

} // Flow

#endif //FLOWENGINE_RENDERER_H
