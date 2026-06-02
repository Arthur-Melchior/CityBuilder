//
// Created by Arthur on 02.06.2026.
//

#ifndef CITYBUILDER_CONTEXT_H
#define CITYBUILDER_CONTEXT_H
#include <vector>

#include "building.h"
#include "market.h"
#include "resource.h"
#include "tile.h"
#include "villager.h"

struct Context {
  std::vector<citybuilder::game::Tile> tiles;
  std::vector<citybuilder::game::Building> buildings;
  std::vector<citybuilder::game::Market> markets;
  std::vector<citybuilder::game::Resource> resources;
  std::vector<citybuilder::game::Villager> villagers;
};

#endif  // CITYBUILDER_CONTEXT_H
