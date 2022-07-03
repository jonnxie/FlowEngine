//
// Created by hasee on 2022/7/3.
//

#ifndef FLOWENGINE_EVENT_H
#define FLOWENGINE_EVENT_H

#include "glm.hpp"

namespace Flow {

    /*
     * Dont care release action
     */
    enum class EventType{
        SingleClick = 0,
        DoubleClick,
        SinglePress,
        DoublePress,
        MouseMove,
        Count,
    };

    struct Event{
    public:
        virtual EventType type() = 0;
    };

    struct SingleClick : public Event{
    public:
        SingleClick(glm::dvec2 _pos): pos(_pos){};
        EventType type() override {return EventType::SingleClick;}
    private:
        glm::dvec2 pos;
        int mouse;
    };

    struct DoubleClick : public SingleClick{
    public:
        EventType type() override {return EventType::DoubleClick;}
    };

    struct SinglePress : public Event{
    public:
        EventType type() override {return EventType::SinglePress;}
    private:
        int key;
    };

    struct DoublePress : public SinglePress{
    public:
        EventType type() override {return EventType::DoublePress;}
    };

    struct MouseMove : public Event{
    public:
        EventType type() override {return EventType::MouseMove;}
    private:
        glm::dvec2 offset;
        int mouse;
    };


} // Flow

#endif //FLOWENGINE_EVENT_H
