//
// Created by hasee on 2022/7/23.
//

#ifndef FLOWENGINE_RENDERCOMPONENT_H
#define FLOWENGINE_RENDERCOMPONENT_H

#include "Macro/Macro.h"
#include <memory>
#include <functional>
#include <utility>

namespace Flow {

    class Material;
    class Renderer;

    class RenderComponent {
    public:
        static SP(RenderComponent) createRenderComponent();
        virtual ~RenderComponent() = default;
    protected:
        RenderComponent() = default;
        explicit RenderComponent(std::function<void(RenderComponent*)> _renderFunction):renderFunction(std::move(_renderFunction)){};
    public:
        virtual void drawIndex(size_t _count, size_t _offset) = 0;
        virtual void draw(size_t _count, size_t _offset) = 0;
        virtual void bindMaterial(Material* _mat) = 0;
        void operator()(RenderComponent* _component) {
            renderFunction(_component);
        }
        Renderer* getRenderer();
        void setRenderer(Renderer* _renderer);
    protected:
        Renderer* renderer{};
        std::function<void(RenderComponent*)> renderFunction;
    };

} // Flow

#endif //FLOWENGINE_RENDERCOMPONENT_H
