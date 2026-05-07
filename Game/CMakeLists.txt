set(SOURCES
        src/game.cc
        include/game.h)

add_library(Game STATIC ${SOURCES})
target_include_directories(Game PUBLIC include)