//
// Created by Kalle on 25.06.2026.
//

#include "placeables/villager.h"
Status citybuilder::game::Villager::Move(const std::vector<Vector2i> &position,
                                         const float delta_time) {
  if (path_index == position.size() - 1) {
    path_index = 0;
    return kSuccess;
  }

  delta_time_ += delta_time;
  if (delta_time_ > 1 / speed) {
    position_ = position.at(++path_index);
  }

  return kRunning;
}