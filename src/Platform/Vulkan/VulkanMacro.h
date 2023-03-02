//
// Created by jonnxie on 2023/3/2.
//

#ifndef ARCHITECTURE_VULKANMACRO_H
#define ARCHITECTURE_VULKANMACRO_H

#ifdef NDEBUG
    #define VKExecute(function) function;
#else
    #define VKExecute(function) VK_CHECK_RESULT(function);
#endif


#endif //ARCHITECTURE_VULKANMACRO_H
