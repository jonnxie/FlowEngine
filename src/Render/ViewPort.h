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
        explicit ViewPort(UP(ViewPortSpec) _spec): m_spec(std::move(_spec)){};
        virtual ~ViewPort() = default;
        static SP(ViewPort) createViewPort(UP(ViewPortSpec) _spec);
    public:
        std::pair<uint32_t, uint32_t> getOffset()
        {
            return {m_spec->x, m_spec->x};
        }
        std::pair<uint32_t, uint32_t> getExtent()
        {
            return {m_spec->width, m_spec->height};
        }
        Camera& getCamera()
        {
            return m_spec->camera;
        }
        void setFrameBuffer(const std::vector<AttachFormat>& _formats,
        uint32_t _samples = 1,
        bool _swapChainTarget = false)
        {
            UP(FrameBufferSpecification) spec = std::make_unique<FrameBufferSpecification>(m_spec->width, m_spec->height,
                                          _formats,
                                          _samples,
                                          _swapChainTarget);
            frameBuffer = FrameBuffer::createFramebuffer(std::move(spec));
        }
        SP(FrameBuffer)& getFrameBuffer()
        {
            return frameBuffer;
        }
    private:
        UP(ViewPortSpec) m_spec;
        SP(FrameBuffer) frameBuffer{nullptr};
    };
}

#endif //FLOWENGINE_VIEWPORT_H
