//
// Created by Kalle on 14.05.2026.
//

#ifndef CITYBUILDER_TILE_H
#define CITYBUILDER_TILE_H

#include <array>

namespace citybuilder::game {

class Tile {
 public:
  Tile(const std::array<float, 2> position,
       const std::array<float, 2> texture_coords)
      : position_(position),
        texture_coords_(texture_coords) {
  }

  [[nodiscard]] std::array<float, 2> GetPosition() const {
    return position_;
  }

  [[nodiscard]] std::array<float, 2> GetTextureCoords() const {
    return texture_coords_;
  }

 private:
  std::array<float, 2> position_;
  std::array<float, 2> texture_coords_;
};

//resource ?

}  // namespace citybuilder::game

#endif  // CITYBUILDER_TILE_H
