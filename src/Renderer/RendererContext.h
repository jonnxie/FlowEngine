//
// Created by hasee on 2022/6/30.
//

#ifndef FLOWENGINE_RENDERERCONTEXT_H
#define FLOWENGINE_RENDERERCONTEXT_H

#include <cstdint>
#include <utility>
#include "Macro/Macro.h"
#include <memory>
namespace Flow {

    class RendererContext {
    public:
        virtual ~RendererContext() = default;
        static SP(RendererContext) get();
        virtual void saveScreenshot(std::basic_string<char> filename) = 0;
        std::pair<uint32_t, uint32_t> getPresentExtent() {return presentExtent;}
    private:
        std::pair<uint32_t, uint32_t> presentExtent{};
    };

} // Flow

#endif //FLOWENGINE_RENDERERCONTEXT_H
