//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_RENDERER_H
#define FLOWENGINE_RENDERER_H

#include <vector>

namespace Flow {

class FrameBuffer;
class Scene;

    class Renderer {
    public:
        virtual bool init() = 0;
        virtual void render(Scene* scene) = 0;
        virtual void attachFrameBuffer(FrameBuffer* frameBuffer) = 0;
    };

} // Flow

#endif //FLOWENGINE_RENDERER_H
