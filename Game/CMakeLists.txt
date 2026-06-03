set(SOURCES
        src/game.cc
        include/game.h
        include/tile.h
        include/villager.h
        include/market.h
        include/resource.h
        include/building.h
        include/random_generator.h
        include/placeable.h
        include/vector2.h
        include/display_box.h
        include/context.h
        include/BehaviourTree/node.h
        include/BehaviourTree/action_node.h
        include/BehaviourTree/selector_node.h
        include/BehaviourTree/sequence_node.h
)

add_library(Game STATIC ${SOURCES})
target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC API)
