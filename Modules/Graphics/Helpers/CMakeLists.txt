set(TARGET MethaneGraphicsHelpers)

include(Methane)

get_module_dirs("Methane/Graphics")

set(HEADERS
    ${INCLUDE_DIR}/Helpers.h
    ${INCLUDE_DIR}/Camera.h
    ${INCLUDE_DIR}/Timer.h
    ${INCLUDE_DIR}/FpsCounter.h
    ${INCLUDE_DIR}/Mesh.h
    ${INCLUDE_DIR}/MathTypes.h
    ${INCLUDE_PLATFORM_DIR}/Helpers.h
    ${INCLUDE_PLATFORM_DIR}/MathTypes.h
)

set(SOURCES
    ${SOURCES_DIR}/Camera.cpp
    ${SOURCES_DIR}/Timer.cpp
    ${SOURCES_DIR}/FpsCounter.cpp
    ${SOURCES_DIR}/Mesh.cpp
)

add_library(${TARGET} STATIC
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${TARGET}
    PRIVATE
        Sources
    PUBLIC
        Include
)

target_link_libraries(${TARGET}
    CML
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
