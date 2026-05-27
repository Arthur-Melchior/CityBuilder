//
// Created by Arthur on 23.05.2026.
//

#ifndef CITYBUILDER_POSITION_DATA_H
#define CITYBUILDER_POSITION_DATA_H

#include "vector2f.h"

struct PositionData {
  PositionData(const Vector2f position,
               const Vector2f texture_coords)
      : position(position), texture_coords(texture_coords) {}
  PositionData() = delete;

  Vector2f position;
  Vector2f texture_coords;
};

template <typename T>
concept HasPosition = requires(T a) {
  { a.position_data } -> std::same_as<PositionData&>;
};

#endif  // CITYBUILDER_POSITION_DATA_H
