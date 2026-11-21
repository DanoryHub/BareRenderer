file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/tgaimage/*.hpp")
set(SOURCES
        ${HEADERS}
        tgaimage.cpp
)

add_library(tga STATIC ${SOURCES})
target_include_directories(tga PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")