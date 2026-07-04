//
// Created by Arthur on 07.05.2026.
//

#include <game.h>
#include <placeables/tile.h>

#include <random>

#include "../../API/include/file/save_manager.h"
#include "../../API/include/graphics/fast_noise_lite.h"
#include "../../API/include/graphics/renderer.h"
#include "behaviour_tree/action_node.h"
#include "behaviour_tree/behaviour_tree_node.h"
#include "behaviour_tree/selector_node.h"
#include "graphics/renderer_display_box.h"
#include "pathfinding/pathfinder.h"
#include "placeables/building.h"
#include "placeables/display_box.h"
#include "placeables/horizontal_layout.h"
#include "placeables/placeable.h"
#include "utils/context.h"

void citybuilder::game::Game::StartGame() {
  tiles_ = GenerateRandomTiles(2);
  std::vector<Resource> resources = GenerateRandomResources(2);
  graphics::Renderer renderer(1920, 1080, "City Builder", false);
  sf::Clock clock{};
  // Pathfinder pathfinder{tiles, world_size_width_, world_size_height_};
  // auto path = pathfinder.FindPath({0, 0}, {100, 100});

  Building b{{0, 0}, {5, 10}, {5, 2}};

  const int width = static_cast<int>(tiles_.size()) / world_size_width_ - 1;
  const int height = static_cast<int>(tiles_.size()) / world_size_height_ - 1;

  b.position = {random_generator_.Random(0, width),
                random_generator_.Random(0, height)};

  while (!CanPlace(b, tiles_, world_size_width_)) {
    b.position = {random_generator_.Random(0, width),
                  random_generator_.Random(0, height)};
  }

  Place(b, tiles_, world_size_width_);
  std::vector buildings{b};

  DisplayBox test{{30, 0}, {8, 10}, {200, 200}};
  test.text = "test";
  test.font_size = 50;

  HorizontalLayout horizontal_layout{};
  horizontal_layout.display_box.position = {0, 1080 - 200};
  horizontal_layout.display_box.size = {1920, 200};
  horizontal_layout.display_box.texture_coords = {8, 10};
  horizontal_layout.display_box.is_button = false;
  DisplayBox d1{{0, 0}, {9, 9}, {100, 100}, "", 20, true};
  d1.action = [&]() -> void {
    renderer.SetHologramVisibility(true);
    renderer.ChangeHologramTexture(d1.texture_coords);
  };
  DisplayBox d2{{0, 0}, {6, 10}, {100, 100}, "", 20, true};
  d2.action = [&]() -> void {
    renderer.SetHologramVisibility(true);
    renderer.ChangeHologramTexture(d2.texture_coords);
  };
  horizontal_layout.AddChild(d1);
  horizontal_layout.AddChild(d2);

  std::vector ui{horizontal_layout.display_box};
  for (auto& child : *horizontal_layout.GetChildren()) {
    ui.push_back(child);
  }

  // SelectorNode node;
  // ActionNode wander;
  // wander.action = []() { return kSuccess; };
  // node.children.emplace_back(&wander);

  renderer.FirstRender(tiles_, buildings, resources, ui);
  std::vector<Vector2i> p{{20, 20}, {21, 20}, {22, 20}, {23, 20},
                          {24, 20}, {25, 20}, {26, 20}, {27, 20}};
  while (renderer.Render()) {
    for (auto& villager : *NPCManager::GetVillagers()) {
      villager.Move(p, clock.getElapsedTime().asSeconds());
      clock.restart();
    }
  }
}

std::vector<citybuilder::game::Tile>
citybuilder::game::Game::GenerateRandomTiles(const int seed) {
  std::vector<Tile> tiles;
  fast_noise_lite noise;

  noise.SetNoiseType(fast_noise_lite::NoiseType_Cellular);
  noise.SetSeed(seed);
  noise.SetFrequency(0.04f);
  noise.SetCellularReturnType(fast_noise_lite::CellularReturnType_CellValue);
  noise.SetCellularDistanceFunction(
      fast_noise_lite::CellularDistanceFunction_Hybrid);
  noise.SetCellularJitter(1);
  noise.SetFractalType(fast_noise_lite::FractalType_None);

  for (int i = 0; i < world_size_width_; ++i) {
    for (int j = 0; j < world_size_height_; ++j) {
      const auto noiseValue =
          noise.GetNoise(static_cast<float>(i), static_cast<float>(j));

      const Vector2i position = {i, j};
      const Vector2i texture_coords = {3, 2};

      Tile tile(position, texture_coords);

      if (noiseValue < -0.5f) {
        tile.texture_coords = {7, 4};
        tile.is_walkable = false;
      } else if (noiseValue < 0) {
        tile.texture_coords = {2, 4};
      } else if (noiseValue < 0.5f) {
        tile.texture_coords = {3, 9};
      }

      tiles.push_back(tile);
    }
  }

  return tiles;
}

std::vector<citybuilder::game::Resource>
citybuilder::game::Game::GenerateRandomResources(const int seed) const {
  std::vector<Resource> resources;
  fast_noise_lite noise;
  noise.SetNoiseType(fast_noise_lite::NoiseType_Perlin);
  noise.SetSeed(seed);
  noise.SetFrequency(0.1f);
  noise.SetFractalType(fast_noise_lite::FractalType_PingPong);
  noise.SetFractalGain(0.01f);

  for (int i = 0; i < world_size_width_; ++i) {
    for (int j = 0; j < world_size_height_; ++j) {
      if (!tiles_.at(i * world_size_width_ + j).is_walkable) continue;

      const auto noiseValue =
          noise.GetNoise(static_cast<float>(i), static_cast<float>(j));

      const Vector2i position = {i, j};
      const Vector2i texture_coords = {-1, -1};

      Resource resource{{""}, position, texture_coords, {1, 1}};

      if (noiseValue < 0.5f && noiseValue > 0.25f) {
        resource.name = "egg";
        resource.texture_coords = {0, 3};
      } else if (noiseValue < 0.75f && noiseValue > 0.25f) {
        resource.name = "carrot";
        resource.texture_coords = {10, 9};
      } else if (noiseValue < 1.f && noiseValue > 0.25f) {
        resource.name = "pumpkin";
        resource.texture_coords = {4, 5};
      }

      resources.push_back(resource);
    }
  }
  return resources;
}