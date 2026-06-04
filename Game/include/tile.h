//
// Created by Arthur on 14.05.2026.
//

#ifndef CITYBUILDER_TILE_H
#define CITYBUILDER_TILE_H

#include "placeable.h"

namespace citybuilder::game {

struct Tile {
  Tile(const Vector2i position, const Vector2i texture_coords, const Vector2f size = {32,32})
      : position(position), texture_coords(texture_coords), size(size) {}
  Tile(const Vector2i position, const Vector2i texture_coords,
       const bool is_walkable)
      : position(position),
        texture_coords(texture_coords),
        is_walkable(is_walkable) {}

  Vector2i position;
  Vector2i texture_coords;
  Vector2f size{32, 32};

  bool is_walkable = true;
};

// resource ?

}  // namespace citybuilder::game

#endif  // CITYBUILDER_TILE_H
