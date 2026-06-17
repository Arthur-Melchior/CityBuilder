//
// Created by Kalle on 10.06.2026.
//

#include "pathfinding/pathfinder.h"
#include <optional>

std::vector<Vector2i> Pathfinder::FindPath(Vector2i starting_position,
                                           Vector2i target_position) {
  const auto diff = starting_position - target_position;
  const auto distance = static_cast<float>(diff.x + diff.y);
  PathNode currentNode({starting_position.x, starting_position.y}, distance, 0,
                       distance, nullptr);

  std::vector<Vector2i> path;

  while (currentNode.position != target_position) {
    currentNode.Neighbors =
        GetNeighbors(&currentNode, target_position, currentNode.cost + 0.5f);
    if (auto cheapestChoice = weight_queue_.top();
        cheapestChoice != currentNode) {
      currentNode = cheapestChoice;
    } else {
      currentNode.isDeadEnd = true;
      currentNode.priority = std::numeric_limits<float>::max();
    }
  }

  std::reverse(path.begin(), path.end());
  return path;
}

std::array<PathNode*, 8> Pathfinder::GetNeighbors(
    PathNode* path_node, const Vector2i target_position, const float cost) {
  std::array<PathNode*, 8> neighbors{};
  neighbors[0] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x, path_node->position.y - 1}, cost);
  neighbors[1] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x + 1, path_node->position.y - 1}, cost + 0.4f);
  neighbors[2] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x + 1, path_node->position.y}, cost);
  neighbors[3] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x + 1, path_node->position.y + 1}, cost + 0.4f);
  neighbors[4] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x, path_node->position.y + 1}, cost);
  neighbors[5] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x - 1, path_node->position.y + 1}, cost + 0.4f);
  neighbors[6] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x - 1, path_node->position.y - 1}, cost);
  neighbors[7] = GeneratePathNode(
      path_node, target_position,
      {path_node->position.x - 1, path_node->position.y - 1}, cost);
  return neighbors;
}

PathNode* Pathfinder::GeneratePathNode(PathNode* parentNode,
                                       Vector2i target_position,
                                       const Vector2i new_node_position,
                                       const float cost) {
  int x = new_node_position.x;
  int y = new_node_position.y;
  if (std::optional node = path_node_map_[x][y]) {
    return &node.value();
  }

  if (x < 0) {
    x = 0;
  } else if (x >= map_.extent(0)) {
    x = static_cast<int>(map_.extent(0) - 1);
  }

  if (y < 0) {
    y = 0;
  } else if (y >= map_.extent(1)) {
    y = static_cast<int>(map_.extent(1) - 1);
  }

  const auto distance =
      static_cast<float>(target_position.Distance(target_position));

  path_node_map_[x][y] = PathNode ({x, y}, distance, cost, distance + cost, parentNode);
  weight_queue_.push(path_node_map_[x][y]);

  return &path_node_map_[x][y];
}