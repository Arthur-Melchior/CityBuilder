set(SOURCES
        src/game.cc
        include/game.h
        include/tile.h
        include/villager.h
        include/market.h
        include/resource.h
        include/building.h
        include/random_generator.h
        include/position_data.h
        include/Vector2f.h
        include/display_box.h
)

add_library(Game STATIC ${SOURCES})
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC API)
