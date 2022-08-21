//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_RENDERERCONTEXT_H
#define FLOWENGINE_RENDERERCONTEXT_H

#include <cstdint>
#include <utility>
#include "Macro/Macro.h"
#include <memory>
#include "Window/window.h"

namespace Flow {

    class RendererContext {
    public:
        RendererContext(Window* _window): window(_window){};
        virtual ~RendererContext() = default;
        static void createRenderContext(Window* _window);
        static SP(RendererContext) get();
        virtual void saveScreenshot(std::basic_string<char> filename) = 0;
        std::pair<uint32_t, uint32_t> getPresentExtent() {return (*window)();}
    private:
        static SP(RendererContext) context;
    protected:
        Window* window;
    };

} // Flow

#endif //FLOWENGINE_RENDERERCONTEXT_H
