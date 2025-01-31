set(TARGET MethaneGraphicsExtensions)

include(Methane)

get_module_dirs("Methane/Graphics")

set(HEADERS
    ${INCLUDE_DIR}/Extensions.h
)

set(SOURCES
    ${SOURCES_DIR}/ImageLoader.cpp
    ${INCLUDE_DIR}/ImageLoader.h
)

add_library(${TARGET} STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${TARGET}
    MethanePlatformUtils
    MethaneGraphicsCore
)

if (METHANE_USE_OPEN_IMAGE_IO)
    target_link_libraries(${TARGET} OpenImageIO)
    target_compile_definitions(${TARGET}
        PRIVATE
        USE_OPEN_IMAGE_IO
    )
    set_target_properties(${TARGET}
        PROPERTIES
        PREREQUISITE_MODULES "OpenImageIO"
    )
else()
    target_link_libraries(${TARGET} STB)
endif()

target_include_directories(${TARGET}
    PRIVATE
        Sources
    PUBLIC
        Include
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

