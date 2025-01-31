set(TARGET MethaneKit)

get_module_dirs("Methane")

set(SOURCES
    ${SOURCES_DIR}/Kit.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/Kit.h
)

add_library(${TARGET} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${TARGET}
    PRIVATE
        Sources
    PUBLIC
        Include
)

target_link_libraries(${TARGET}
    PUBLIC
        MethaneDataTypes
        MethaneGraphicsApp
        MethaneGraphicsCore
        MethaneGraphicsHelpers
        MethaneGraphicsExtensions
)

set(PREREQUISITE_TARGETS
    MethaneGraphicsExtensions
)
add_prerequisite_modules(${TARGET} "${PREREQUISITE_TARGETS}")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

set_target_properties(${TARGET}
    PROPERTIES
    FOLDER Modules
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET}
    INCLUDES
        DESTINATION ${INCLUDE_DIR}
        COMPONENT Development
    PUBLIC_HEADER
        DESTINATION ${INCLUDE_DIR}
        COMPONENT Development
    ARCHIVE
        DESTINATION Lib
        COMPONENT Development
)