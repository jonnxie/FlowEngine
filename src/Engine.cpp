//
// Created by hasee on 2022/6/29.
//

#include "Engine.h"

#include <utility>
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
            window->update();
            renderer->render(scene.get());
            computer->compute(scene.get());
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
    }

    void Engine::end() {
        running = false;
    }
} // FlowEngine