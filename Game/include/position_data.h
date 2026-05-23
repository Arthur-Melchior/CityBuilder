//
// Created by Arthur on 23.05.2026.
//

#ifndef CITYBUILDER_POSITION_DATA_H
#define CITYBUILDER_POSITION_DATA_H
#include <array>

struct PositionData {
  PositionData(const std::array<int, 2> position,
               const std::array<int, 2> texture_coords)
      : position(position), texture_coords(texture_coords) {}

  std::array<int, 2> position;
  std::array<int, 2> texture_coords;
};

#endif  // CITYBUILDER_POSITION_DATA_H
