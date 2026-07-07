//
// Created by Kalle on 25.06.2026.
//

#include "placeables/villager.h"
// void citybuilder::game::Villager::Tick() {
//
// }
Status citybuilder::game::Villager::Move(const std::vector<Vector2i> &path,
                                         const float delta_time) {
  if (path.empty() || position == path.back()) {
    path_index = 0;
    return kSuccess;
  }

  delta_time_ += delta_time;
  if (delta_time_ > 1 / speed) {
    this->position = path.at(path_index);
    delta_time_ = 0;
    path_index++;
  }

  return kRunning;
}