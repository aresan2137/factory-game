cmake_minimum_required(VERSION 3.24)
project(Game LANGUAGES CXX)

include(FetchContent)

set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE GAME_SOURCES "src/**.cpp")
add_executable(Game ${GAME_SOURCES})

target_include_directories(Game PUBLIC ${raylib_SOURCE_DIR}/src)
target_link_libraries(Game PUBLIC raylib)

add_custom_command(
    TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/resources
        $<TARGET_FILE_DIR:Game>/resources
)

set_property(TARGET Game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:Game>)