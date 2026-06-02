//
// Created by Arthur on 02.06.2026.
//

#include "save_manager.h"
void SaveManager::Save(Context& context, const std::string& file_path) {
  nlohmann::json save;

  save["tiles"] = nlohmann::json::array();

  for (auto& tile : context.tiles) {
    save["tiles"].push_back({{"x", tile.position_data.position.x},
                             {"y", tile.position_data.position.y},
                             {"is_walkable", tile.is_walkable}});
  }

  std::ofstream file(file_path);
  file << save.dump(2);
}

Context SaveManager::Load(const std::string& file_path) {
  std::ifstream file(file_path);

  nlohmann::json data = nlohmann::json::parse(file);

  Context context;

  for (const auto& tile_json : data["tiles"]) {
    auto x = tile_json["x"].get<float>();
    auto y = tile_json["y"].get<float>();
    auto is_walkable = tile_json["is_walkable"].get<bool>();

    citybuilder::game::Tile tile{{x, y}, {0, 0}, is_walkable};

    context.tiles.push_back(tile);
  }

  return context;
}