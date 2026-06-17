//
// Created by Arthur on 23.05.2026.
//

#ifndef CITYBUILDER_PLACEABLE_H
#define CITYBUILDER_PLACEABLE_H

#include "utils/vector2.h"

template <typename T>
concept Placeable = requires(T a) {
  {a.position} -> std::same_as<Vector2i&>;
  {a.texture_coords} -> std::same_as<Vector2i&>;
  {a.size} -> std::same_as<Vector2i&>;
};

#endif  // CITYBUILDER_PLACEABLE_H
