set(TARGET MethaneGraphicsCore)

include(Methane)

get_module_dirs("Methane/Graphics")

if (WIN32)

    set(PLATFORM_SOURCES
        ${SOURCES_GRAPHICS_DIR}/TypesDX.h
        ${SOURCES_GRAPHICS_DIR}/TypesDX.cpp
        ${SOURCES_GRAPHICS_DIR}/ContextDX.h
        ${SOURCES_GRAPHICS_DIR}/ContextDX.cpp
        ${SOURCES_GRAPHICS_DIR}/ShaderDX.h
        ${SOURCES_GRAPHICS_DIR}/ShaderDX.cpp
        ${SOURCES_GRAPHICS_DIR}/ProgramDX.h
        ${SOURCES_GRAPHICS_DIR}/ProgramDX.cpp
        ${SOURCES_GRAPHICS_DIR}/ResourceDX.h
        ${SOURCES_GRAPHICS_DIR}/ResourceDX.cpp
        ${SOURCES_GRAPHICS_DIR}/DescriptorHeapDX.h
        ${SOURCES_GRAPHICS_DIR}/DescriptorHeapDX.cpp
        ${SOURCES_GRAPHICS_DIR}/BufferDX.h
        ${SOURCES_GRAPHICS_DIR}/BufferDX.cpp
        ${SOURCES_GRAPHICS_DIR}/TextureDX.h
        ${SOURCES_GRAPHICS_DIR}/TextureDX.cpp
        ${SOURCES_GRAPHICS_DIR}/SamplerDX.h
        ${SOURCES_GRAPHICS_DIR}/SamplerDX.cpp
        ${SOURCES_GRAPHICS_DIR}/CommandQueueDX.h
        ${SOURCES_GRAPHICS_DIR}/CommandQueueDX.cpp
        ${SOURCES_GRAPHICS_DIR}/RenderCommandListDX.h
        ${SOURCES_GRAPHICS_DIR}/RenderCommandListDX.cpp
        ${SOURCES_GRAPHICS_DIR}/RenderPassDX.h
        ${SOURCES_GRAPHICS_DIR}/RenderPassDX.cpp
        ${SOURCES_GRAPHICS_DIR}/RenderStateDX.h
        ${SOURCES_GRAPHICS_DIR}/RenderStateDX.cpp
    )

    set(PLATFORM_LIBRARIES
        D3DX12
        d3d12
        dxgi
        d3dcompiler
    )

    set(EXTRA_COMPILE_OPTIONS
        # Disable useless compiler warnings
        /wd4250 # C4250: this warning is compiler bug: https://stackoverflow.com/questions/469508/visual-studio-compiler-warning-c4250-class1-inherits-class2member-via-d
    )

elseif(APPLE)

    set(PLATFORM_SOURCES
        ${SOURCES_GRAPHICS_DIR}/TypesMT.h
        ${SOURCES_GRAPHICS_DIR}/TypesMT.mm
        ${SOURCES_GRAPHICS_DIR}/ContextMT.h
        ${SOURCES_GRAPHICS_DIR}/ContextMT.mm
        ${SOURCES_GRAPHICS_DIR}/ShaderMT.h
        ${SOURCES_GRAPHICS_DIR}/ShaderMT.mm
        ${SOURCES_GRAPHICS_DIR}/ProgramMT.h
        ${SOURCES_GRAPHICS_DIR}/ProgramMT.mm
        ${SOURCES_GRAPHICS_DIR}/RenderStateMT.h
        ${SOURCES_GRAPHICS_DIR}/RenderStateMT.mm
        ${SOURCES_GRAPHICS_DIR}/ResourceMT.h
        ${SOURCES_GRAPHICS_DIR}/ResourceMT.mm
        ${SOURCES_GRAPHICS_DIR}/DescriptorHeapMT.h
        ${SOURCES_GRAPHICS_DIR}/DescriptorHeapMT.mm  
        ${SOURCES_GRAPHICS_DIR}/BufferMT.h
        ${SOURCES_GRAPHICS_DIR}/BufferMT.mm
        ${SOURCES_GRAPHICS_DIR}/TextureMT.h
        ${SOURCES_GRAPHICS_DIR}/TextureMT.mm
        ${SOURCES_GRAPHICS_DIR}/SamplerMT.h
        ${SOURCES_GRAPHICS_DIR}/SamplerMT.mm
        ${SOURCES_GRAPHICS_DIR}/RenderPassMT.h
        ${SOURCES_GRAPHICS_DIR}/RenderPassMT.mm
        ${SOURCES_GRAPHICS_DIR}/CommandQueueMT.h
        ${SOURCES_GRAPHICS_DIR}/CommandQueueMT.mm
        ${SOURCES_GRAPHICS_DIR}/RenderCommandListMT.h
        ${SOURCES_GRAPHICS_DIR}/RenderCommandListMT.mm
    )

    set(PLATFORM_LIBRARIES
        "-framework Metal"
    )

    # CLANG_ENABLE_OBJC_WEAK = YES
    set_source_files_properties(
        ${PLATFORM_SOURCES}
        PROPERTIES
        COMPILE_FLAGS -fobjc-weak
    )

endif()

set(LIBRARIES ${PLATFORM_LIBRARIES}
    MethaneDataTypes
    MethaneRangeSet
    MethanePlatformUtils
    MethanePlatformAppView
    MethaneGraphicsHelpers
    IttNotify
)

set(HEADERS
    ${INCLUDE_DIR}/Context.h
    ${INCLUDE_DIR}/Shader.h
    ${INCLUDE_DIR}/Program.h
    ${INCLUDE_DIR}/Resource.h
    ${INCLUDE_DIR}/Buffer.h
    ${INCLUDE_DIR}/Texture.h
    ${INCLUDE_DIR}/Sampler.h
    ${INCLUDE_DIR}/CommandQueue.h
    ${INCLUDE_DIR}/CommandList.h
    ${INCLUDE_DIR}/RenderCommandList.h
    ${INCLUDE_DIR}/RenderState.h
    ${INCLUDE_DIR}/RenderPass.h
    ${INCLUDE_DIR}/Types.h
)

set(SOURCES ${PLATFORM_SOURCES}

    # Native alias headers
    ${SOURCES_DIR}/Native/ContextNT.h
    ${SOURCES_DIR}/Native/ShaderNT.h
    ${SOURCES_DIR}/Native/ProgramNT.h
    ${SOURCES_DIR}/Native/ResourceNT.h
    ${SOURCES_DIR}/Native/DescriptorHeapNT.h
    ${SOURCES_DIR}/Native/BufferNT.h
    ${SOURCES_DIR}/Native/TextureNT.h
    ${SOURCES_DIR}/Native/SamplerNT.h
    ${SOURCES_DIR}/Native/CommandQueueNT.h
    ${SOURCES_DIR}/Native/RenderCommandListNT.h
    ${SOURCES_DIR}/Native/RenderStateNT.h
    ${SOURCES_DIR}/Native/RenderPassNT.h

    # Base implementation
    ${SOURCES_DIR}/ObjectBase.h
    ${SOURCES_DIR}/ContextBase.h
    ${SOURCES_DIR}/ContextBase.cpp
    ${SOURCES_DIR}/ShaderBase.h
    ${SOURCES_DIR}/ShaderBase.cpp
    ${SOURCES_DIR}/ProgramBase.h
    ${SOURCES_DIR}/ProgramBase.cpp
    ${SOURCES_DIR}/ResourceBase.h
    ${SOURCES_DIR}/ResourceBase.cpp
    ${SOURCES_DIR}/BufferBase.h
    ${SOURCES_DIR}/BufferBase.cpp
    ${SOURCES_DIR}/TextureBase.h
    ${SOURCES_DIR}/TextureBase.cpp
    ${SOURCES_DIR}/SamplerBase.h
    ${SOURCES_DIR}/SamplerBase.cpp
    ${SOURCES_DIR}/CommandQueueBase.h
    ${SOURCES_DIR}/CommandQueueBase.cpp
    ${SOURCES_DIR}/CommandListBase.h
    ${SOURCES_DIR}/CommandListBase.cpp
    ${SOURCES_DIR}/RenderCommandListBase.h
    ${SOURCES_DIR}/RenderCommandListBase.cpp
    ${SOURCES_DIR}/RenderPassBase.h
    ${SOURCES_DIR}/RenderPassBase.cpp
    ${SOURCES_DIR}/RenderStateBase.h
    ${SOURCES_DIR}/RenderStateBase.cpp

    # Other sources
    ${SOURCES_DIR}/DescriptorHeap.h
    ${SOURCES_DIR}/DescriptorHeap.cpp
    ${SOURCES_DIR}/ResourceManager.h
    ${SOURCES_DIR}/ResourceManager.cpp
    ${SOURCES_DIR}/Instrumentation.h
    ${SOURCES_DIR}/Instrumentation.cpp
    ${SOURCES_DIR}/Types.cpp
)

add_library(${TARGET} STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${TARGET}
    ${LIBRARIES}
)

target_include_directories(${TARGET}
    PRIVATE
        Sources
    PUBLIC
        Include
)

target_compile_options(${TARGET}
    PUBLIC
    ${EXTRA_COMPILE_OPTIONS}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

set_target_properties(${TARGET}
    PROPERTIES
    FOLDER Modules/Render
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET}
    PUBLIC_HEADER
        DESTINATION ${INCLUDE_DIR}
        COMPONENT Development
    ARCHIVE
        DESTINATION Lib
        COMPONENT Development
)
