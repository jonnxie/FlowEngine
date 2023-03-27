//
// Created by hasee on 2022/7/1.
//

#ifndef FLOWENGINE_VIEWPORT_H
#define FLOWENGINE_VIEWPORT_H

#include <cstdint>
#include <utility>
#include "Scene/Camera.h"
#include <memory>
#include "FrameBuffer.h"

namespace Flow{

    struct ViewPortSpec
    {
        uint32_t x{}, y{};
        uint32_t width{}, height{};
        Camera camera;
    };

    UP(ViewPortSpec) makeViewPortSpec(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, const Camera& _camera);

    class ViewPort {
    public:
        ViewPort() = default;
        explicit ViewPort(UP(ViewPortSpec) _spec): spec(std::move(_spec)){};
        virtual ~ViewPort() = default;
        static SP(ViewPort) createViewPort(UP(ViewPortSpec) _spec);
    public:
        std::pair<uint32_t, uint32_t> getOffset()
        {
            return {spec->x, spec->x};
        }
        std::pair<uint32_t, uint32_t> getExtent()
        {
            return {spec->width, spec->height};
        }
        Camera& getCamera()
        {
            return spec->camera;
        }
        void bindFrameBuffer(SP(FrameBuffer) _frameBuffer) { frameBuffer = std::move(_frameBuffer);}
        SP(FrameBuffer) getFrameBuffer() { return frameBuffer;}
    private:
        UP(ViewPortSpec) spec{};
        SP(FrameBuffer) frameBuffer{};
    };
}

#endif //FLOWENGINE_VIEWPORT_H
