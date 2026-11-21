file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/RenderTarget/*.hpp")
file(GLOB CPPS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
set(SOURCES ${HEADERS} ${CPPS})

add_library(RenderTarget STATIC ${SOURCES})
target_link_libraries(RenderTarget PUBLIC SDL3::SDL3-static tga)
target_include_directories(RenderTarget PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")