file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/RenderTarget/*.hpp")
set(SOURCES
    ${HEADERS}
    TGARenderTarget.cpp
)

add_library(RenderTarget STATIC ${SOURCES})
target_include_directories(RenderTarget PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")