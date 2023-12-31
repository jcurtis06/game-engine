cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(example)
include(FetchContent)
include_directories(${CMAKE_SOURCE_DIR}/game_engine)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(json)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} main.cpp
        game_engine/core.cpp
        game_engine/core.h
        game_engine/gameobject/gameobject.cpp
        game_engine/gameobject/gameobject.h
        game_engine/gameobject/components/component.cpp
        game_engine/gameobject/components/component.h
        game_engine/gameobject/components/playercontroller.h
        game_engine/gameobject/components/graphics/sprite_renderer.h
        game_engine/gameobject/components/graphics/tile_map_renderer.h
        game_engine/resources/tile.h
        game_engine/resources/tilemap.h
        game_engine/gameobject/components/physics/kinematic_body.h
        game_engine/gameobject/components/physics/tile_map_collider.h
        game_engine/gameobject/components/graphics/animation_renderer.h
        game_engine/resources/animation.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()