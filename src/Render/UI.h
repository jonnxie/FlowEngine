//
// Created by hasee on 2022/7/7.
//

#ifndef FLOWENGINE_UI_H
#define FLOWENGINE_UI_H

#include <cstdint>
#include "Macro/Macro.h"

namespace Flow {

    class Window;

    class UI {
    public:
        static SP(UI) createUI(Window *_window);
    public:
        virtual bool init() = 0;
        virtual void update() = 0;
        virtual void newFrame() = 0;
        virtual void render() = 0;
    private:

    };

} // Flow

#endif //FLOWENGINE_UI_H
