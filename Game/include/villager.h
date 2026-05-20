//
// Created by Kalle on 18.05.2026.
//

#ifndef CITYBUILDER_VILLAGER_H
#define CITYBUILDER_VILLAGER_H
#include <array>

namespace citybuilder::game {

class Villager {
public:
  float happiness;
  std::array<int,2> position;
};

//happiness
//position
//work (enum)
//do work
//pathfinding ?
//needs

}  // namespace citybuilder::game

#endif  // CITYBUILDER_VILLAGER_H
