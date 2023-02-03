//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_ENGINE_H
#define FLOWENGINE_ENGINE_H

#include <vector>
#include <atomic>
#include <mutex>
#include <cstdint>
#include <chrono>
#include <ctime>
#include "Window/window.h"
#include "Macro/Macro.h"

namespace Flow {

    class Renderer;
    class Computer;
    class Scene;

    typedef std::chrono::time_point<std::chrono::system_clock> time_point;

    enum class ExecuteMode{
        Infinite,
        Limited,
    };

    class Engine {
    public:
        Engine() = default;
        ~Engine() = default;
        DisableCopy(Engine);
    public:
        void init();
        void update();
    public:
        void setScene(UP(Scene) _scene);
        void setWindow(SP(Window) _window);
        void setRenderer(SP(Renderer) _renderer);
        void setComputer(SP(Computer) _computer);
        void setFPS(size_t _fps);
        void setExecuteMode(ExecuteMode _mode);
    protected:
        void render();
        void compute();
        void begin();
        void end();
    private:
        std::atomic<bool> running = false;
        UP(Scene) scene;
        SP(Window) window;
        SP(Renderer) renderer;
        SP(Computer) computer;
        size_t fps{};
        /*
         * nanosecond
         */
        double timing{};
        ExecuteMode executeMode{ExecuteMode::Infinite};
        time_point startTime;
        time_point endTime;
    };

    UP(Engine) makeEngine();

} // Flow

#endif //FLOWENGINE_ENGINE_H
