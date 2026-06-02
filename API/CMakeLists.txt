find_package(SFML 3 REQUIRED COMPONENTS Main System Window Graphics Audio CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

set(SOURCES
        graphics/src/renderer.cc
        graphics/include/renderer.h
        graphics/include/fast_noise_lite.h
        graphics/include/renderer_display_box.h
        graphics/src/renderer_display_box.cc
        file/include/save_manager.h
        file/src/save_manager.cc
)

add_library(API STATIC ${SOURCES})

target_include_directories(API PUBLIC graphics/include file/include ${CMAKE_SOURCE_DIR}/Game/include)
target_link_libraries(API PUBLIC SFML::Main SFML::System SFML::Window SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)