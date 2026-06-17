//
// Created by Kalle on 10.06.2026.
//

#ifndef CITYBUILDER_PATH_NODE_H
#define CITYBUILDER_PATH_NODE_H
#include <array>

#include "utils/vector2.h"

struct PathNode {
  PathNode(const Vector2i position, const float heuristic_distance,
           const float cost, const float priority, PathNode* parent)
      : position(position),
        heuristic_distance(heuristic_distance),
        cost(cost),
        priority(priority),
        parent(parent) {}

  PathNode() = default;
  bool operator==(const PathNode& other) const { return this == &other; }
  bool operator!=(const PathNode& other) const { return this != &other; }
  bool operator<(const PathNode& other) const {
    return priority < other.priority;
  }

  Vector2i position = {0, 0};
  float heuristic_distance = 0;
  float cost = 0;
  float priority = 0;
  bool isDeadEnd = false;
  PathNode* parent{};
  std::array<PathNode*, 8> Neighbors{};
};

#endif  // CITYBUILDER_PATH_NODE_H
