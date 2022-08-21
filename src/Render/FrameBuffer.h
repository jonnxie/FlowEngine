//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_FRAMEBUFFER_H
#define FLOWENGINE_FRAMEBUFFER_H

#include <cstdint>
#include <vector>
#include <memory>
#include "FormatFilter.hpp"
#include "Macro/Macro.h"
#include "Renderer.h"


namespace Flow{

    struct FrameBufferSpecification
    {
        uint32_t Width = 0,
                Height = 0;
        std::vector<AttachFormat> formats{};
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };

    class FrameBuffer {
    public:
        static SP(FrameBuffer) createFramebuffer(UP(FrameBufferSpecification) _spec);
        explicit FrameBuffer(UP(FrameBufferSpecification) _spec):
                m_spec(std::move(_spec))
        {};
        DisableCopy(FrameBuffer);
        virtual ~FrameBuffer()= default;
    public:
        virtual void resize(uint32_t _width,uint32_t _height) = 0;
        virtual void release() = 0;
        virtual void releaseCaptureVals() = 0;

    protected:
        UP(FrameBufferSpecification) m_spec;
    };
}


#endif //FLOWENGINE_FRAMEBUFFER_H
