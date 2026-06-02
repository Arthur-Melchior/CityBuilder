//
// Created by Arthur on 02.06.2026.
//

#include "save_manager.h"
void SaveManager::Save(Context& context, const std::string& file_path) {
  nlohmann::json save;

  save["tiles"] = nlohmann::json::array();
  save["buildings"] = nlohmann::json::array();
  save["markets"] = nlohmann::json::array();
  save["villagers"] = nlohmann::json::array();
  save["resources"] = nlohmann::json::array();

  for (auto& tile : context.tiles) {
    save["tiles"].push_back({{"x", tile.position_data.position.x},
                             {"y", tile.position_data.position.y},
                             {"tex_x", tile.position_data.texture_coords.x},
                             {"tex_y", tile.position_data.texture_coords.y},
                             {"is_walkable", tile.is_walkable}});
  }
  for (auto& building : context.buildings) {
    save["buildings"].push_back(
        {{"x", building.position_data.position.x},
         {"y", building.position_data.position.y},
         {"tex_x", building.position_data.texture_coords.x},
         {"tex_y", building.position_data.texture_coords.y},
         {"size_x", building.size.x},
         {"size_y", building.size.y}});
  }

  for (auto& market : context.markets) {
    save["markets"].push_back({{"name", market.name}});
  }

  for (auto& villager : context.villagers) {
    save["villagers"].push_back({
        {"x", villager.position_data.position.x},
        {"y", villager.position_data.position.y},
        {"tex_x", villager.position_data.texture_coords.x},
        {"tex_y", villager.position_data.texture_coords.y},
        {"happiness", villager.happiness},
    });
  }

  for (auto& resource : context.resources) {
    save["resources"].push_back({{"name", resource.name}});
  }

  std::ofstream file(file_path);
  file << save.dump(2);
}

Context SaveManager::Load(const std::string& file_path) {
  std::ifstream file(file_path);

  nlohmann::json data = nlohmann::json::parse(file);

  Context context;

  for (const auto& tile : data["tiles"]) {
    auto x = tile["x"].get<float>();
    auto y = tile["y"].get<float>();
    auto tex_x = tile["tex_x"].get<float>();
    auto tex_y = tile["tex_y"].get<float>();
    auto is_walkable = tile["is_walkable"].get<bool>();

    citybuilder::game::Tile t{{x, y}, {tex_x, tex_y}, is_walkable};

    context.tiles.push_back(t);
  }

  for (const auto& building : data["buildings"]) {
    auto x = building["x"].get<float>();
    auto y = building["y"].get<float>();
    auto tex_x = building["tex_x"].get<float>();
    auto tex_y = building["tex_y"].get<float>();
    auto size_x = building["size_x"].get<float>();
    auto size_y = building["size_y"].get<float>();

    citybuilder::game::Building b{{{x, y}, {tex_x, tex_y}}, {size_x, size_y}};

    context.buildings.push_back(b);
  }

  for (const auto& market : data["markets"]) {
    auto name = market["name"].get<std::string>();

    citybuilder::game::Market m{name};

    context.markets.push_back(m);
  }

  for (auto& villager : data["villagers"]) {
    auto x = villager["x"].get<float>();
    auto y = villager["y"].get<float>();
    auto tex_x = villager["tex_x"].get<float>();
    auto tex_y = villager["tex_y"].get<float>();
    auto happiness = villager["happiness"].get<float>();

    citybuilder::game::Villager v{{{x, y}, {tex_x, tex_y}}, happiness};

    context.villagers.push_back(v);
  }

  for (auto& resource : data["resources"]) {
    auto name = resource["name"].get<std::string>();

    citybuilder::game::Resource r{name};

    context.resources.push_back(r);
  }

  return context;
}