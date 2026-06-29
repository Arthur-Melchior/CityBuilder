//
// Created by Arthur on 29.06.2026.
//

#ifndef CITYBUILDER_NPC_MANAGER_H
#define CITYBUILDER_NPC_MANAGER_H
#include <vector>

#include "placeables/villager.h"
#include "utils/vector2.h"

class NPCManager {
 public:
  static void SpawnNPC(Vector2i position);
  static std::vector<citybuilder::game::Villager>* GetVillagers() {
    return &npcs_;
  };

 private:
  inline static std::vector<citybuilder::game::Villager> npcs_;
};
inline void NPCManager::SpawnNPC(const Vector2i position) {
  npcs_.push_back(citybuilder::game::Villager{position, {2, 2}, {1, 1}, 0});
}

#endif  // CITYBUILDER_NPC_MANAGER_H
