find_package(SFML 3 REQUIRED COMPONENTS Main System Window Graphics Audio CONFIG REQUIRED)

set(SOURCES
        graphics/src/renderer.cc
        graphics/include/renderer.h
)

add_library(API STATIC ${SOURCES})

target_include_directories(API PUBLIC graphics/include)
target_link_libraries(API PUBLIC SFML::Main SFML::System SFML::Window SFML::Graphics SFML::Audio)