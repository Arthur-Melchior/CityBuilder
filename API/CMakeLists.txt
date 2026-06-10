find_package(SFML 3 REQUIRED COMPONENTS Main System Window Graphics Audio CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

set(SOURCES
        src/graphics/renderer.cc
        include/graphics/renderer.h
        include/graphics/fast_noise_lite.h
        include/graphics/renderer_display_box.h
        src/graphics/renderer_display_box.cc
        include/file/save_manager.h
        src/file/save_manager.cc
)

add_library(API STATIC ${SOURCES})

target_include_directories(API PUBLIC include ${CMAKE_SOURCE_DIR}/Game/include)
target_link_libraries(API PUBLIC SFML::Main SFML::System SFML::Window SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)