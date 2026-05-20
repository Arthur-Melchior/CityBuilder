find_package(SFML 3 REQUIRED COMPONENTS Main System Window Graphics Audio CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

set(SOURCES
        graphics/src/renderer.cc
        graphics/include/renderer.h
        graphics/include/display_box.h
        graphics/include/fast_noise_lite.h
)

add_library(API STATIC ${SOURCES})

target_include_directories(API PUBLIC graphics/include ${CMAKE_SOURCE_DIR}/Game/include)
target_link_libraries(API PUBLIC SFML::Main SFML::System SFML::Window SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)