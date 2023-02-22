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
        static UP(RenderComponent) createRenderComponent(std::function<void(RenderComponent*)> _renderFunction);
        virtual ~RenderComponent() = default;
    protected:
        RenderComponent() = default;
        explicit RenderComponent(std::function<void(RenderComponent*)> _renderFunction):renderFunction(std::move(_renderFunction)){};
    public:
        virtual void drawIndex(size_t _count, size_t _offset){};
        virtual void draw(size_t _count, size_t _offset) {};
        virtual void bindMaterial(const Material* _mat){};
        void operator()(RenderComponent* _component) {
            renderFunction(_component);
        }
        Renderer* getRenderer();
        const Material* getMaterial();
        void setRenderer(Renderer* _renderer);
    protected:
        Material* material{};
        Renderer* renderer{};
        std::function<void(RenderComponent*)> renderFunction;
    };

    class RenderComponentMiddle {
    public:
        RenderComponentMiddle() = default;
        explicit RenderComponentMiddle(std::function<void(RenderComponent*)> _renderFunction);
        ~RenderComponentMiddle() = default;
        RenderComponent* operator()() {return renderComponent.get();}
        RenderComponentMiddle(const RenderComponentMiddle & _middle);
        RenderComponentMiddle(RenderComponentMiddle
                              && _middle) noexcept ;
        RenderComponentMiddle &operator=(const RenderComponentMiddle & _middle);
        RenderComponentMiddle &operator=(RenderComponentMiddle && _middle);
    private:
        std::function<void(RenderComponent*)> renderFunction;
        UP(RenderComponent) renderComponent;
    };



} // Flow

#endif //FLOWENGINE_RENDERCOMPONENT_H
