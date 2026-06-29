//
// Created by Kalle on 10.06.2026.
//

#ifndef CITYBUILDER_PATHFINDER_H
#define CITYBUILDER_PATHFINDER_H

#include <mdspan>
#include <optional>
#include <queue>
#include <vector>

#include "placeables/tile.h"

class Pathfinder {
 public:
  Pathfinder(std::vector<citybuilder::game::Tile>& tiles, const int rows,
             const int cols)
      : width_(cols), height_(rows), map_(tiles.data(), rows, cols) {
    path_node_map_.resize(rows * cols);
  }

  std::vector<Vector2i> FindPath(Vector2i starting_position,
                                 Vector2i target_position);

 private:
  int width_ = 0;
  int height_ = 0;
  float heuristic_force = 2.f;
  std::mdspan<citybuilder::game::Tile, std::dextents<size_t, 2>> map_;
  std::vector<uint8_t> path_node_map_;
  ///@brief the first float is the priority and the second is the index
  std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>,
                      std::greater<>>
      weight_queue_;
  std::vector<Vector2i> positions_;
  std::vector<float> distances_;
  std::vector<float> costs_;
  std::vector<float> priorities_;
  std::vector<float> parents_;
  void CalculateNeighbors(int current_node, Vector2i target_position);
  void CalculatePathNode(int parent, Vector2i target_position,
                         Vector2i new_node_position, float cost);
};

#endif  // CITYBUILDER_PATHFINDER_H
