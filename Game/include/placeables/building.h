//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_BUILDING_H
#define CITYBUILDER_BUILDING_H

#include "npc_manager.h"
#include "placeable.h"

namespace citybuilder::game {

enum BuildingType {
  Cantina,
  Woodcutter,
  Farmer,
  Miner,
};

class Building {
 public:
  Building(Vector2i position, Vector2i text_coords, Vector2i size,
           BuildingType building_type)
      : position(position),
        texture_coords(text_coords),
        size(size),
        building_type(building_type) {
    OnCreate();
  }
  Vector2i position;
  Vector2i texture_coords;
  Vector2i size;
  BuildingType building_type;
  void OnCreate() const;

 private:
};

inline void Building::OnCreate() const {
  for (int i = 0; i < 5; ++i) {
    if (building_type == Woodcutter) {
      NPCManager::SpawnNPC(position, {1, 0});
    } else if (building_type == Farmer) {
      NPCManager::SpawnNPC(position, {2, 0});
    } else if (building_type == Miner) {
      NPCManager::SpawnNPC(position, {3, 0});
    }
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
