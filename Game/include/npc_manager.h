//
// Created by Arthur on 29.06.2026.
//

#ifndef CITYBUILDER_NPC_MANAGER_H
#define CITYBUILDER_NPC_MANAGER_H
#include <vector>

#include "villager.h"
#include "utils/vector2.h"

class NPCManager {
 public:
  static void SpawnNPC(Vector2i position, Vector2i text_coords, citybuilder::game::VillagerJob villager_job);
  static std::vector<citybuilder::game::Villager>* GetVillagers() {
    return &npcs_;
  };

 private:
  inline static std::vector<citybuilder::game::Villager> npcs_;
};
inline void NPCManager::SpawnNPC(const Vector2i position, const Vector2i text_coords,
                                 const citybuilder::game::VillagerJob villager_job) {
  npcs_.push_back(citybuilder::game::Villager{position, text_coords, {1, 1}, 0, villager_job});
}

#endif  // CITYBUILDER_NPC_MANAGER_H
