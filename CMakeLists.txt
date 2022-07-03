cmake_minimum_required(VERSION 3.22)
project(FlowEngine)

set(CMAKE_CXX_STANDARD 23)
# ....................

file(GLOB CORE
        "src/*.cpp"
        "src/*.h"
        "src/*/*.cpp"
        "src/*/*.h"
        "src/*/*/*.cpp"
        "src/*/*/*.h"
        )
file(GLOB IMGUI
        "thirdparty/imgui-docking/*.cpp"
        "thirdparty/imgui-docking/backends/imgui_impl_glfw.*"
        "thirdparty/imgui-docking/backends/imgui_impl_vulkan.*"
        "thirdparty/imgui-docking/*.h")

set(KTX_DIR thirdparty/ktx)
set(KTX_SOURCES
        ${KTX_DIR}/lib/texture.c
        ${KTX_DIR}/lib/hashlist.c
        ${KTX_DIR}/lib/checkheader.c
        ${KTX_DIR}/lib/swap.c
        ${KTX_DIR}/lib/memstream.c
        ${KTX_DIR}/lib/filestream.c
        ${KTX_DIR}/include/ktx.h
        ${KTX_DIR}/include/ktxvulkan.h
        )

add_library(ktx STATIC ${KTX_SOURCES})

set(REFLECT_DIR thirdparty/spirv_reflect)
set(REFLECT_SOURCES
        ${REFLECT_DIR}/spirv_reflect.h
        ${REFLECT_DIR}/spirv_reflect.c)
add_library(reflect STATIC ${REFLECT_SOURCES})

add_compile_definitions(FLOW_GRAPHICS_VULKAN)

add_library(FlowEngine SHARED ${CORE} ${IMGUI})

## VulKan
find_package(Vulkan REQUIRED)

target_include_directories(FlowEngine PUBLIC
        thirdparty/imgui-docking
        thirdparty/imgui-docking/backends
        src/
        thirdparty/ktx/include/
        thirdparty/stb-master/
        thirdparty/tinyobjloader-master/
        thirdparty/tinygltf/
#        thirdparty/glfw-3.3.4.bin.WIN64/include/
        thirdparty/glm/
        thirdparty/Entt/
        thirdparty/json/
        ${Vulkan_INCLUDE_DIRS}
        ${REFLECT_DIR})

target_link_libraries(FlowEngine
        ktx
        glfw3
        ${Vulkan_LIBRARIES}
        reflect
        )

#set(CMAKE_C_FLAGS "-static")
##set(CMAKE_LINK_LIBRARY_FLAG "-static")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
#set(CMAKE_EXE_LINKER_FLAGS "-static")









