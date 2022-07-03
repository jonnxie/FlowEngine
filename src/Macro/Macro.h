//
// Created by hasee on 2022/6/29.
//

#ifndef FLOWENGINE_MACRO_H
#define FLOWENGINE_MACRO_H

#include <glm.hpp>
#include <string>
#include <map>

namespace Flow {

#define VertexShader    0
#define FragmentShader  1
#define ComputeShader   2
#define RayGen          3
#define RayMiss         4
#define RayClosest      5
#define TaskShader      6
#define MeshShader      7

    enum class AssemState{
        Point_List,
        Line_Strip,
        Line_List,
        Triangle_List,
        Triangle_Strip,
    };

    enum class BlendState{
        /*
         * no transparent
         */
        Default,
        CPU_Particle,
        Particle,
        GPass,
        Capture,
    };

    enum class RenderPassType{
        CascadeShadow,
        OffScreen,
        Capture,
        Present,
        Color,
    };

    enum class RasterState{
        Point,
        Polyline,
        TriangleLine,
        TriangleFace,
        CPU_Particle,
        Marching_Cube,
        Back_Face,
    };

    enum class DrawType{
        Index,
        Vertex,
        Indirect,
    };

    enum class MultisampleState{
        Default,
    };

    enum class DepthStencilState{
        Default,
        UnderScreenLine,
        DepthWriteDisable,
        DepthDisable,
        MaxDepth,
    };

    enum class DrawObjectType{
        Default,
        OffScreen,
        Transparency,
        Normal,
        AABB,
    };

    const glm::vec3 RED_COLOR{1.0f,0.0f,0.0f};
    const glm::vec3 YELLOW_COLOR{1.0f,1.0f,0.0f};
    const glm::vec3 GREEN_COLOR{0.0f,0.5f,0.0f};
    const glm::vec3 PURPLE_COLOR{0.5f,0.0f,0.5f};
    const glm::vec3 BLUE_COLOR{0.0f,0.0f,1.0f};
    const glm::vec3 CYAN_COLOR{0.0f,1.0f,1.0f};
    const glm::vec3 GOLD_COLOR{1.0f,0.84f,0.0f};
    const glm::vec3 ORANGE_COLOR{1.0f,0.64f,0.0f};
    const glm::vec3 WHITE_COLOR{1.0f,1.0f,1.0f};
    const glm::vec3 BLACK_COLOR{0.0f,0.0f,0.0f};

    const glm::vec3 UpDirection{0.0f, 0.0f, 1.0f};
    const glm::vec3 DownDirection{0.0f, 0.0f, -1.0f};
    const glm::vec3 LeftDirection{-1.0f, 0.0f, 0.0f};
    const glm::vec3 RightDirection{1.0f, 0.0f, 0.0f};
    const glm::vec3 ForwardDirection{0.0f, 1.0f, 0.0f};
    const glm::vec3 BackDirection{0.0f, -1.0f, 0.0f};

#define pai 3.1415926535897932384626433832795
#define two_pai 6.283185307179586476925286766559
#define half_pai 1.5707963267948966192313216916398
//#define degree (pai/180.0f)
#define degree 0.01745329251994329576923690768489
#define float_limit 0.000001f

#define one_byte 1
#define one_vec2 8
#define one_vec3 12
#define one_vec4 16
#define one_matrix 64

#define defaultModelCount 20

#define CaptureBoxVertexCount 36

//#define ObjectCatalog      "Engine/Object/object.h"
//#define CObjectCatalog     "Engine/Object/cobject.h"
//#define DObjectCatalog     "Engine/Object/dobject.h"
//#define GObjectCatalog     "Engine/Object/gobject.h"
//#define SceneCatalog       "Engine/Object/scene.h"
//#define MPoolCatalog       "Engine/Pool/mpool.h"
//#define BPoolCatalog       "Engine/Pool/bpool.h"
//#define PPoolCatalog       "Engine/Pool/ppool.h"
//#define DeviceCatalog      "Engine/Object/device.h"
//#define SetPoolCatalog     "Engine/Pool/setpool.h"
//#define SlbPoolCatalog     "Engine/Pool/slbpool.h"
//#define ModelSetCatalog    "Engine/Pool/modelsetpool.h"
//#define TaskCatalog        "Engine/Event/taskpool.h"
//#define ShaderCatalog      "Engine/Pool/shaderpool.h"
//#define TexturePoolCatalog "Engine/Pool/TexturePool.h"
//#define GLTFCatalog        "Engine/Object/VulkanglTFModels.h"
//#define CameraCatalog      "Engine/Object/camera.h"
//#define SGroupCatalog      "Engine/Pool/shadergrouppool.h"
//#define OffScreenCatalog   "Engine/Object/offscreen.h"
//#define ListenerCatalog    "Engine/Object/listener.h"
//#define CaptureCatalog     "Engine/Object/CaptureObject.h"
//#define MathCatalog        "Engine/Item/shatter_math.h"
//#define MemPoolCatalog     "Engine/Pool/mempool.hpp"
//#define InputTypeCatalog   "Engine/Object/inputtype.h"
//#define InputActionCatalog "Engine/Object/inputaction.h"
//#define PrecompiledCatalog "precompiledhead.h"
//#define AABBCatalog        "Engine/Object/aabb.h"
//#define BufferCatalog      "Engine/Buffer/shatterbufferinclude.h"
//#define PipelineCatalog    "Engine/Renderer/pipeline.h"
//#define RenderCatalog      "Engine/Renderer/shatter_render_include.h"
//#define PCatalog           "Engine/Renderer/pipeline.h"
//#define AppCatalog         "Engine/App/shatterapp.h"
//#define ManipulateCatalog  "Engine/Base/Manipulate.h"
//
//#define ItemCatalog        "Engine/Item/shatter_item.h"
//#define MacroCatalog       "Engine/Item/shatter_macro.h"
//#define ConfigCatalog      "Engine/Item/configs.h"
//#define UniformCatalog     "Engine/Item/uniform.h"
//
//#define GuiCatalog         "Engine/Base/GUI.h"
//#define DPointCatalog      "Engine/Base/points.h"
//#define DLineCatalog       "Engine/Base/lines.h"
//#define HandleCatalog      "Engine/Base/handle.h"
//#define OperatorCatalog    "Engine/Base/operator.h"

#define ShaderFilePath      "D:/FlowEngine/data/shaders"
#define ModelFilePath       "F:/ASSET/models/"
#define TextureFilePath     "F:/ASSET/textures/"
#define B3DMPath            "F:/ASSET/b3dm/"
#define I3DMPath            "F:/ASSET/i3dm/"
#define AnimationPath       "C:/Users/AnWell/Desktop/ASSET/animation/"

#define DisableCopy(Class) \
Class(const Class&) = delete;\
Class(Class&&) = delete;\
Class& operator = (const Class&) = delete;\
Class& operator = (Class&&) = delete


#define UP(Object) std::unique_ptr<Object>

#define SP(Object) std::shared_ptr<Object>

#define GuardMutex(lock) std::lock_guard<std::mutex> lockGuard(lock);

#define throwFile(x) throw std::runtime_error(std::string("no such file ") + x)

#define ClassProtectedReferenceElement(elementName, elementType, funcName) \
    protected:                                                    \
    elementType elementName{};                                    \
    public:                                                       \
    elementType& get##funcName()                                  \
    {                                                             \
        return elementName;                                       \
    }

#define GuardLock(lock) std::lock_guard<std::mutex> lockGuard(lock);


} // FlowEngine

#endif //FLOWENGINE_MACRO_H
