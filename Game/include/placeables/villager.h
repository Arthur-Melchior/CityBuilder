//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_VILLAGER_H
#define CITYBUILDER_VILLAGER_H

#include "../behaviour_tree/behaviour_tree_node.h"
#include "placeable.h"
#include "vector"

namespace citybuilder::game {

class Villager {
 public:
  Villager(const Vector2i position, const Vector2i text_coords,
           const Vector2i size, const float happiness)
      : position(position),
        texture_coords(text_coords),
        size(size),
        happiness(happiness) {}

  Vector2i position{0, 0};
  Vector2i texture_coords{0, 0};
  Vector2i size{0, 0};
  float speed = 0;
  // std::unique_ptr<Node> bt_root ;
  float happiness = 0;
  Status Move(const std::vector<Vector2i> &position, float delta_time);

 private:
  float delta_time_ = 0;
  int path_index = 0;
};

// happiness
// position
// work (enum)
// do work
// pathfinding ?
// needs

}  // namespace citybuilder::game

#endif  // CITYBUILDER_VILLAGER_H
