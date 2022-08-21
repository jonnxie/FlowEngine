//
// Created by hasee on 2022/8/18.
//

#ifndef FLOWENGINE_UICOMPONENT_H
#define FLOWENGINE_UICOMPONENT_H

#include "Macro/Macro.h"

namespace Flow {

    class UIComponent {
    public:
        static SP(UIComponent) createUIComponent();
    public:
        virtual void button() = 0;
        virtual void text() = 0;
    };



} // Flow

#endif //FLOWENGINE_UICOMPONENT_H
