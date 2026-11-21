CMAKE_MINIMUM_REQUIRED(VERSION 4.0.0)
PROJECT(BareRenderer)

include(FetchContent)

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.20
)
FetchContent_MakeAvailable(SDL3)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/RenderTarget)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/tgaimage)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        RenderTarget
)