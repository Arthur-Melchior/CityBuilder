//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_VILLAGER_H
#define CITYBUILDER_VILLAGER_H
#include <array>

#include "position_data.h"

namespace citybuilder::game {

class Villager {
public:
  PositionData position_data;
  float happiness{};
 };

//happiness
//position
//work (enum)
//do work
//pathfinding ?
//needs

}  // namespace citybuilder::game

#endif  // CITYBUILDER_VILLAGER_H
