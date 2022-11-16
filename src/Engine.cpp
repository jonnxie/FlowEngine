//
// Created by hasee on 2022/6/29.
//

#include "Engine.h"

#include <utility>
#include <ctime>
#include <thread>
#include "Render/Renderer.h"
#include "Compute/Computer.h"
#include "Window/window.h"
#include "Scene/Scene.h"

namespace Flow {
    void Engine::init() {

    }

    void Engine::update() {
        while (running)
        {
            begin();
            compute();
            render();
            end();
        }
    }

    void Engine::setScene(std::unique_ptr<Scene> _scene) {
        scene = std::move(_scene);
    }

    void Engine::setWindow(std::shared_ptr<Window> _window) {
        window = std::move(_window);
    }

    void Engine::setRenderer(std::shared_ptr<Renderer> _renderer) {
        renderer = std::move(_renderer);
    }

    void Engine::setComputer(std::shared_ptr<Computer> _computer) {
        computer = std::move(_computer);
    }

    void Engine::begin() {
        running = true;
        if (executeMode == ExecuteMode::Limited)
        {
            startTime = std::chrono::system_clock::now();
        }
        window->update();
    }

    void Engine::end() {
        running = false;
        if (executeMode == ExecuteMode::Limited)
        {
            endTime = std::chrono::system_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            if (ms < timing)
            {
                auto time = std::chrono::microseconds(uint64_t(timing - ms));
                std::this_thread::sleep_for(time);
            }
        }
    }

    void Engine::render() {
        renderer->render(scene.get());
    }

    void Engine::compute() {
        computer->compute(scene.get());
    }

    void Engine::setFPS(size_t _fps) {
        fps = _fps;
        timing = 1000.0f / double(_fps);
    }

    void Engine::setExecuteMode(ExecuteMode _mode) {
        executeMode = _mode;
    }
} // FlowEngine