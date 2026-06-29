set(SOURCES
        src/game.cc
        include/game.h
        include/placeables/tile.h
        include/placeables/villager.h
        include/market.h
        include/placeables/resource.h
        include/placeables/building.h
        include/utils/random_generator.h
        include/placeables/placeable.h
        include/utils/vector2.h
        include/placeables/display_box.h
        include/utils/context.h
        include/behaviour_tree/behaviour_tree_node.h
        include/behaviour_tree/action_node.h
        include/behaviour_tree/selector_node.h
        include/behaviour_tree/sequence_node.h
        include/pathfinding/pathfinder.h
        include/pathfinding/path_node.h
        src/pathfinding/pathfinder.cpp
        include/placeables/horizontal_layout.h
        src/horizontal_layout.cc
        include/npc_manager.h
)

add_library(Game STATIC ${SOURCES})
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC API)
