//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_BUILDING_H
#define CITYBUILDER_BUILDING_H
#include <array>
#include <vector>

#include "position_data.h"
#include "tile.h"

namespace citybuilder::game {

class Building {
 public:
  PositionData position_data;
  int size_x;
  int size_y;
};

// cost
// position
// output
// workers
// min workers
// max workers
// output modifier

}  // namespace citybuilder::game

#endif  // CITYBUILDER_BUILDING_H
