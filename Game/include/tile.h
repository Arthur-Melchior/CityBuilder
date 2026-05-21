//
// Created by Kalle on 14.05.2026.
//

#ifndef CITYBUILDER_TILE_H
#define CITYBUILDER_TILE_H

#include <array>

namespace citybuilder::game {

struct Tile {
  Tile(const std::array<float, 2> position,
       const std::array<float, 2> texture_coords)
      : position(position),
        texture_coords(texture_coords) {
  }

  std::array<float, 2> position;
  std::array<float, 2> texture_coords;

  bool is_walkable = false;
};

//resource ?

}  // namespace citybuilder::game

#endif  // CITYBUILDER_TILE_H
