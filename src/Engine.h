//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_ENGINE_H
#define FLOWENGINE_ENGINE_H

#include <vector>
#include <atomic>
#include <mutex>
#include <cstdint>
#include "Window/window.h"
#include "Macro/Macro.h"

namespace Flow {

    class Renderer;
    class Computer;
    class Scene;

    class Engine {
    public:
        void init();
        void update();
    public:
        void setScene(UP(Scene) _scene);
        void setWindow(SP(Window) _window);
        void setRenderer(SP(Renderer) _renderer);
        void setComputer(SP(Computer) _computer);
        void begin();
        void end();
    private:
        std::atomic<bool> running = false;
        UP(Scene) scene;
        SP(Window) window;
        SP(Renderer) renderer;
        SP(Computer) computer;
    };

} // Flow

#endif //FLOWENGINE_ENGINE_H
