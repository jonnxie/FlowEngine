//
// Created by jonnxie on 2022/5/6.
//

#include "window.h"
#include "imgui.h"
#include "glm.hpp"

namespace Flow{

    void GLFWWindow::windowResized(int _width, int _height) {
        width = _width;
        height = _height;
    }

    void GLFWWindow::keyCallback(int _key, int _action) {
        if(_action == GLFW_PRESS)
        {
            pressKey(_key);
        } else if(_action == GLFW_RELEASE)
        {
            releaseKey(_key);
        }
    }

    void GLFWWindow::mouseCallback(int _button, int _action, double _xPos, double _yPos) {
        if (_action == GLFW_PRESS)
        {
            pressMouse(_button, glm::dvec2(_xPos, _yPos));
        } else if(_action == GLFW_RELEASE)
        {
            releaseMouse(_button);
        }
    }

    void GLFWWindow::cursorPositionCallback(double _xPos, double _yPos) {
        cursorPos = glm::dvec2(_xPos, _yPos);
    }

    void GLFWWindow::scrollCallback(double _xOffset, double _yOffset) {
        scrollPos = glm::dvec2(_xOffset, _yOffset);
    }

    void GLFWWindow::keyTypeCallback(unsigned int _code) {
        ImGuiIO& io = ImGui::GetIO();
        if(_code > 0 && _code < 0x10000)
        {
            io.AddInputCharacter((unsigned short)_code);
        }
    }

    static void windowResizedStatic(GLFWwindow *_window, int _width, int _height) {
        printf("Window resized!\n");
        auto *w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(_window));
        w->windowResized(_width, _height);
    }

    static void keyCallbackStatic(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) {
        auto *w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(_window));
        w->keyCallback(_key, _action);
    }

    static void mouseCallbackStatic(GLFWwindow* _window, int _button, int _action, int _mods) {
        auto *w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(_window));
        double xpos, ypos;
        glfwGetCursorPos(_window, &xpos, &ypos);
        w->mouseCallback(_button, _action, xpos, ypos);
    }

    static void cursorPositionCallbackStatic(GLFWwindow* _window, double _xPos, double _yPos) {
        auto *w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(_window));
        w->cursorPositionCallback(_xPos, _yPos);
    }

    static void scrollCallbackStatic(GLFWwindow* _window, double _xOffset, double _yOffset) {
        auto *w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(_window));
        w->scrollCallback(_xOffset, _yOffset);
    }

    static void keyTypeCallbackStatic(GLFWwindow* _window, unsigned int _code) {
        auto *w = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(_window));
        w->keyTypeCallback(_code);
    }

    void GLFWWindow::init() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        initCursor();

        glfwSetWindowUserPointer(window, this);

        glfwSetWindowSizeCallback(window, windowResizedStatic);

        glfwSetKeyCallback(window, keyCallbackStatic);

        glfwSetMouseButtonCallback(window, mouseCallbackStatic);

        glfwSetCursorPosCallback(window, cursorPositionCallbackStatic);

        glfwSetScrollCallback(window, scrollCallbackStatic);

        glfwSetCharCallback(window, keyTypeCallbackStatic);
    }

    void GLFWWindow::initCursor() {
        m_ImGuiMouseCursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        m_ImGuiMouseCursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
        m_ImGuiMouseCursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);   // FIXME: GLFW doesn't have this.
        m_ImGuiMouseCursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
        m_ImGuiMouseCursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
        m_ImGuiMouseCursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);  // FIXME: GLFW doesn't have this.
        m_ImGuiMouseCursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);  // FIXME: GLFW doesn't have this.
        m_ImGuiMouseCursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    }

    GLFWWindow::~GLFWWindow() {
        for (auto cursor : m_ImGuiMouseCursors){
            glfwDestroyCursor(cursor);
        }
        glfwDestroyWindow(window);
    }

    void Window::pressKey(int _key) {
        pressKeys[_key] = true;
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[_key] =  true;
    }

    void Window::releaseKey(int _key) {
        pressKeys[_key] = false;
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[_key] = false;
    }

    void Window::pressMouse(int _mouse, glm::dvec2 _pos) {
        pressMouses[_mouse] = true;
        cursorPressPos = _pos;
    }

    void Window::releaseMouse(int _mouse) {
        pressMouses[_mouse] = false;
    }

    void Window::update() {
        events.clear();
    }

}


