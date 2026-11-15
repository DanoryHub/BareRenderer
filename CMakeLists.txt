CMAKE_MINIMUM_REQUIRED(VERSION 4.0.0)
PROJECT(BareRenderer)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/tgaimage.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})