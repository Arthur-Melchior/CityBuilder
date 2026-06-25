//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_VILLAGER_H
#define CITYBUILDER_VILLAGER_H

#include "../behaviour_tree/behaviour_tree_node.h"
#include "placeable.h"

namespace citybuilder::game {

class Villager {
public:
  Vector2i texture_coords;
  Vector2i size;
  float speed = 0;
  //std::unique_ptr<Node> bt_root ;
  float happiness = 0;
  Status Move(const std::vector<Vector2i> &position, float delta_time);

private:
  Vector2i position_;
  float delta_time_ = 0;
  int path_index = 0;
 };

//happiness
//position
//work (enum)
//do work
//pathfinding ?
//needs

}  // namespace citybuilder::game

#endif  // CITYBUILDER_VILLAGER_H
