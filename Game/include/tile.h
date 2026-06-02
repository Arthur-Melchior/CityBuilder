//
// Created by Arthur on 14.05.2026.
//

#ifndef CITYBUILDER_TILE_H
#define CITYBUILDER_TILE_H

#include "position_data.h"

namespace citybuilder::game {

struct Tile {
  Tile(const Vector2f position, const Vector2f texture_coords)
      : position_data(position, texture_coords) {
  }
  Tile(const Vector2f position, const Vector2f texture_coords,
       const bool is_walkable)
      : position_data(position, texture_coords), is_walkable(is_walkable) {
  }

  PositionData position_data;

  bool is_walkable = true;
};

//resource ?

}  // namespace citybuilder::game

#endif  // CITYBUILDER_TILE_H
