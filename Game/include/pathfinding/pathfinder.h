//
// Created by Kalle on 10.06.2026.
//

#ifndef CITYBUILDER_PATHFINDER_H
#define CITYBUILDER_PATHFINDER_H

#include <mdspan>
#include <vector>

#include "../placeables/tile.h"
#include "path_node.h"

class Pathfinder {
 public:
  Pathfinder(std::vector<citybuilder::game::Tile>& tiles, const size_t rows,
             const size_t cols)
      : width_(static_cast<int>(cols)),
        height_(static_cast<int>(rows)),
        map_(tiles.data(), rows, cols) {}

  std::vector<Vector2i> FindPath(Vector2i starting_position,
                                 Vector2i target_position);

 private:
  int width_;
  int height_;
  std::mdspan<citybuilder::game::Tile, std::dextents<size_t, 2>> map_;
  std::vector<PathNode> path_node_map_;
  PathNode FindCheapestNode();
  std::array<PathNode*, 8> GetNeighbors(PathNode path_node, float cost);
  PathNode GeneratePathNode();
};

#endif  // CITYBUILDER_PATHFINDER_H
