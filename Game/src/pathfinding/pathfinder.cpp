//
// Created by Kalle on 10.06.2026.
//

#include "pathfinding/pathfinder.h"

#include <optional>

int max_iterations = 10000;

std::vector<Vector2i> Pathfinder::FindPath(Vector2i starting_position,
                                           Vector2i target_position) {
  positions_.clear();
  distances_.clear();
  costs_.clear();
  priorities_.clear();
  parents_.clear();
  while (!weight_queue_.empty()) weight_queue_.pop();
  path_node_map_.clear();

  // create first node
  const auto distance = starting_position.Distance(target_position);
  positions_.push_back(starting_position);
  distances_.push_back(distance);
  costs_.push_back(0);
  priorities_.push_back(distance);
  path_node_map_[starting_position.x * width_ + starting_position.y] = true;
  weight_queue_.push({0, 0});

  int current_iteration = 0;
  int current_node = 0;

  while (positions_.at(current_node) != target_position &&
         current_iteration++ < max_iterations) {
    auto [priority, index] = weight_queue_.top();
    weight_queue_.pop();
    current_node = index;

    CalculateNeighbors(current_node, target_position);
  }

  std::vector<Vector2i> path;
  while (current_node != 0) {
    path.push_back(positions_.at(current_node));
    current_node = parents_.at(current_node - 1);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

void Pathfinder::CalculateNeighbors(const int current_node,
                                    const Vector2i target_position) {
  auto current_position = positions_.at(current_node);
  const auto current_cost = costs_.at(current_node);
  CalculatePathNode(current_node, target_position,
                    {current_position.x, current_position.y - 1},
                    current_cost + 1);
  CalculatePathNode(current_node, target_position,
                    {current_position.x + 1, current_position.y},
                    current_cost + 1);
  CalculatePathNode(current_node, target_position,
                    {current_position.x, current_position.y + 1},
                    current_cost + 1);
  CalculatePathNode(current_node, target_position,
                    {current_position.x - 1, current_position.y},
                    current_cost + 1);
}

void Pathfinder::CalculatePathNode(const int parent, Vector2i target_position,
                                   Vector2i new_node_position, float cost) {
  // sanitize inputs
  int x = new_node_position.x;
  int y = new_node_position.y;

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

  // checks if already exists or unwalkable
  if (path_node_map_[x * width_ + y] || !map_[x, y].is_walkable) {
    return;
  }

  const auto distance =
      new_node_position.Distance(target_position) * heuristic_force;
  const auto priority = distance + cost;

  positions_.push_back(new_node_position);
  distances_.push_back(distance);
  costs_.push_back(cost);
  priorities_.push_back(priority);
  parents_.push_back(parent);
  path_node_map_[x * width_ + y] = true;
  weight_queue_.push({priority, distances_.size() - 1});
}