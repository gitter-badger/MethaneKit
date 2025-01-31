set(TARGET MethanePlatformApp)

include(Methane)

get_module_dirs("Methane/Platform")

if (WIN32)

    set(PLATFORM_HEADERS
        ${INCLUDE_PLATFORM_DIR}/AppWin.h
    )

    set(PLATFORM_SOURCES
        ${SOURCES_PLATFORM_DIR}/AppWin.cpp
    )

elseif(APPLE)

    set(PLATFORM_HEADERS
        ${INCLUDE_PLATFORM_DIR}/AppMac.h
        ${SOURCES_PLATFORM_DIR}/AppDelegate.h
        ${SOURCES_PLATFORM_DIR}/AppViewController.h
    )

    set(PLATFORM_SOURCES
        ${SOURCES_PLATFORM_DIR}/AppMac.mm
        ${SOURCES_PLATFORM_DIR}/AppDelegate.mm
        ${SOURCES_PLATFORM_DIR}/AppViewController.mm
    )

    set(LIBRARIES
        "-framework AppKit"
    )

endif()

set(LIBRARIES ${LIBRARIES}
    MethaneDataTypes
    MethanePlatformUtils
    MethanePlatformAppView
    nowide_static
    cxxopts
)

set(HEADERS ${PLATFORM_HEADERS}
    ${INCLUDE_DIR}/AppBase.h
    ${INCLUDE_DIR}/App.h
)

set(SOURCES ${PLATFORM_SOURCES}
    ${SOURCES_DIR}/AppBase.cpp
)

add_library(${TARGET} STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${TARGET}
    ${LIBRARIES}
)

target_compile_definitions(${TARGET}
    PRIVATE
    METHANE_RENDER_APP
)

target_include_directories(${TARGET}
    PRIVATE
        Sources
    PUBLIC
        Include
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

set_target_properties(${TARGET}
    PROPERTIES
    FOLDER Modules/Platform
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
