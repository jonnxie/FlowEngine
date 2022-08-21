//
// Created by jonnxie on 2022/5/6.
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <utility>
#include <GLFW/glfw3.h>
#include <string>
#include "Macro/Macro.h"
#include "glm.hpp"
#include <unordered_map>
#include <map>
#include "Event.h"
#include <vector>

namespace Flow{
    class Window {
    public:
        Window(int _width, int _height, std::string  _title):width(_width), height(_height), title(std::move(_title)) {}

        virtual ~Window() = default;
    public:
        std::pair<int, int> operator()() {
            return std::make_pair(width, height);
        }
    public:
        virtual void update();
        ClassProtectedReferenceElement(events, std::vector<Event>, Events);
    private:
        virtual void windowResized( int width, int height) = 0;
        virtual void keyCallback( int key, int action) = 0;
        virtual void mouseCallback(int button, int action, double xPos, double yPos) = 0;
        virtual void cursorPositionCallback( double xPos, double yPos) = 0;
        virtual void scrollCallback( double xOffset, double yOffset) = 0;
        virtual void keyTypeCallback( unsigned int code) = 0;
    protected:
        int width;
        int height;
        std::string title{"Flow"};
        std::map<int, bool> pressKeys;
        std::map<int, bool> pressMouses;
        ClassProtectedReferenceElement(cursorPos, glm::dvec2, CursorPos);
        ClassProtectedReferenceElement(cursorPressPos, glm::dvec2, CursorPressPos);
        ClassProtectedReferenceElement(scrollPos, glm::dvec2, ScrollPos);
    protected:
        void pressKey(int _key);
        void releaseKey(int _key);
        void pressMouse(int _mouse, glm::dvec2 _pos);
        void releaseMouse(int _mouse);
    };

    class GLFWWindow : public Window {
    public:
        GLFWWindow(int _width, int _height, std::string  _title) : Window(_width, _height, std::move(_title)){
            init();
        }
        ~GLFWWindow() override;
    public:
        void keyCallback(int _key, int _action) override;
        void windowResized(int _width, int _height) override;
        void mouseCallback(int _button, int _action, double _xPos, double _yPos) override;
        void cursorPositionCallback( double _xPos, double _yPos) override;
        void scrollCallback( double _xOffset, double _yOffset) override;
        void keyTypeCallback( unsigned int _code) override;
    public:
        GLFWwindow* get(){
            return window;
        }
    private:
        void init();
    private:
        GLFWwindow *window{};
        GLFWcursor* m_ImGuiMouseCursors[8] = { 0 };
    private:
        void initCursor();
    };
}

#endif //MAIN_WINDOW_H
