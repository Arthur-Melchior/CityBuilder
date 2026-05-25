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
  PositionData() = default;

  std::array<int, 2> position;
  std::array<int, 2> texture_coords;
};

template <typename T>
concept HasPosition = requires(T a) {
  { a.position_data } -> std::same_as<PositionData&>;
};

#endif  // CITYBUILDER_POSITION_DATA_H
