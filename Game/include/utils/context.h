//
// Created by Arthur on 02.06.2026.
//

#ifndef CITYBUILDER_CONTEXT_H
#define CITYBUILDER_CONTEXT_H
#include <vector>

#include "market.h"
#include "placeables/building.h"
#include "placeables/resource.h"
#include "placeables/villager.h"
#include "placeables/tile.h"

struct Context {
  std::vector<citybuilder::game::Tile> tiles;
  std::vector<citybuilder::game::Building> buildings;
  std::vector<citybuilder::game::Market> markets;
  std::vector<citybuilder::game::Resource> resources;
  std::vector<citybuilder::game::Villager> villagers;
};

#endif  // CITYBUILDER_CONTEXT_H
