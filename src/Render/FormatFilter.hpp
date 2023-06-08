//
// Created by AnWell on 2022/3/1.
//

#ifndef MAIN_FORMATFILTER_HPP
#define MAIN_FORMATFILTER_HPP

enum class TextureFormat{
    RGBA8U,

    DEPTH24STENCIL8,
    Depth = DEPTH24STENCIL8
};

enum class Usage{
    Color,
    Depth
};

typedef union ClearColorValue {
    float       float32[4];
    int32_t     int32[4];
    uint32_t    uint32[4];
} ClearColorValue;

typedef struct ClearDepthStencilValue {
    float       depth;
    uint32_t    stencil;
} ClearDepthStencilValue;

typedef union ClearValue {
    ClearColorValue           color;
    ClearDepthStencilValue    depthStencil;
} ClearValue;

struct AttachFormat{
    TextureFormat format;
    Usage usage;
    ClearValue clearValue;
};

#endif //MAIN_FORMATFILTER_HPP
