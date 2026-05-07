find_package(SFML COMPONENTS Graphics Window Audio System REQUIRED)

set(SOURCES
        graphics/src/draw.cc
        graphics/include/draw.h)

add_library(API STATIC ${SOURCES})

target_include_directories(API PUBLIC graphics/include)
target_link_libraries(API PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)