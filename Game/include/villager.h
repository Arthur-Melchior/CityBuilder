//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_VILLAGER_H
#define CITYBUILDER_VILLAGER_H

#include "placeable.h"

namespace citybuilder::game {

class Villager {
public:
  Vector2i position;
  Vector2i texture_coords;
  Vector2f size;
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
