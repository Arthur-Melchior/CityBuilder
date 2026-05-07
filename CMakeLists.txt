cmake_minimum_required(VERSION 3.15)
project(CityBuilder)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(API)
add_subdirectory(Game)

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/_assets
        ${CMAKE_BINARY_DIR}/_assets
)

add_executable(CityBuilder main.cpp)
target_link_libraries(CityBuilder PRIVATE API Game)
