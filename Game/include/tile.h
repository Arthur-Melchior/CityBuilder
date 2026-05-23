//
// Created by Arthur on 14.05.2026.
//

#ifndef CITYBUILDER_TILE_H
#define CITYBUILDER_TILE_H

#include <array>

#include "position_data.h"

namespace citybuilder::game {

struct Tile {
  Tile(const std::array<int, 2> position,
       const std::array<int, 2> texture_coords)
      : position_data(position, texture_coords) {
  }

  PositionData position_data;

  bool is_walkable = true;
};

//resource ?

}  // namespace citybuilder::game

#endif  // CITYBUILDER_TILE_H
