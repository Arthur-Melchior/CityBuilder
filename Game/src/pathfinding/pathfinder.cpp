//
// Created by Kalle on 10.06.2026.
//

#include "pathfinding/pathfinder.h"

std::vector<Vector2i> Pathfinder::FindPath(Vector2i starting_position,
                                           Vector2i target_position) {
  const auto diff = starting_position - target_position;
  const auto distance = static_cast<float>(diff.x + diff.y);
  PathNode currentNode({starting_position.x, starting_position.y}, distance, 0,
                       distance, nullptr);

  std::vector<Vector2i> path;

  while (currentNode.position != target_position) {
    currentNode.Neighbors = GetNeighbors(currentNode, currentNode.cost + 0.5f);
  }

  std::reverse(path.begin(), path.end());
  return path;
}