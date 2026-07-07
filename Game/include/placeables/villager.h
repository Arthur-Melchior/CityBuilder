//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_VILLAGER_H
#define CITYBUILDER_VILLAGER_H

#include "../behaviour_tree/behaviour_tree_node.h"
#include "behaviour_tree/selector_node.h"
#include "resource.h"
#include "vector"

namespace citybuilder::game {

enum VillagerJob {
  jMiner,
  jWoodcutter,
  jFarmer,
  jLazyBum,
};

class Villager {
 public:
  Villager(const Vector2i position, const Vector2i text_coords,
           const Vector2i size, const float happiness, const VillagerJob job)
      : position(position),
        texture_coords(text_coords),
        size(size),
        happiness(happiness),
        job(job) {}

  Vector2i position{0, 0};
  Vector2i texture_coords{0, 0};
  Vector2i size{0, 0};
  float speed = 3;
  // std::unique_ptr<Node> bt_root ;
  float happiness = 0;
  VillagerJob job;
  Resource* resource_to_find = nullptr;
  // void Tick() { bt_.Tick(); };
  Status Move(const std::vector<Vector2i>& path, float delta_time);
  Status move_status = kFailure;
  std::vector<Vector2i> current_path;
 private:
  float delta_time_ = 0;
  int path_index = 0;
  // SelectorNode bt_{};
};

// happiness
// position
// work (enum)
// do work
// pathfinding ?
// needs

}  // namespace citybuilder::game

#endif  // CITYBUILDER_VILLAGER_H
