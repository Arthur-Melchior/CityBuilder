//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_BUILDING_H
#define CITYBUILDER_BUILDING_H

#include "npc_manager.h"
#include "placeable.h"

namespace citybuilder::game {

class Building {
 public:
  Building(Vector2i position, Vector2i text_coords, Vector2i size)
      : position(position), texture_coords(text_coords), size(size) {
    OnCreate();
  }
  Vector2i position;
  Vector2i texture_coords;
  Vector2i size;
  void OnCreate() const;

 private:
};

inline void Building::OnCreate() const {
  for (int i = 0; i < 5; ++i) {
    NPCManager::SpawnNPC(position);
  }
}

// cost
// position
// output
// workers
// min workers
// max workers
// output modifier

}  // namespace citybuilder::game

#endif  // CITYBUILDER_BUILDING_H
