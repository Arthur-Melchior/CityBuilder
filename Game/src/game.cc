//
// Created by Arthur on 07.05.2026.
//

#include <game.h>
#include <placeables/tile.h>

#include <random>

#include "../../API/include/file/save_manager.h"
#include "../../API/include/graphics/fast_noise_lite.h"
#include "../../API/include/graphics/renderer.h"
#include "placeables/building.h"
#include "placeables/placeable.h"
#include "utils/context.h"
#include "behaviour_tree/action_node.h"
#include "behaviour_tree/behaviour_tree_node.h"
#include "behaviour_tree/selector_node.h"
#include "placeables/display_box.h"
#include "graphics/renderer_display_box.h"

void citybuilder::game::Game::StartGame() const {
  std::vector<Tile> tiles = GenerateRandomTiles();

  Building b{{0, 0}, {5, 10}, {5, 2}};

  const int width = static_cast<int>(tiles.size()) / world_size_width_ - 1;
  const int height = static_cast<int>(tiles.size()) / world_size_height_ - 1;

  b.position = {random_generator_.Random(0, width),
                random_generator_.Random(0, height)};

  while (!CanPlace(b, tiles, world_size_width_)) {
    b.position = {random_generator_.Random(0, width),
                  random_generator_.Random(0, height)};
  }

  Place(b, tiles, world_size_width_);
  std::vector buildings{b};

  DisplayBox test{{30, 0}, {8, 10}, {200, 200}};
  test.text = "test";
  test.font_size = 50;

  std::vector ui{test};

  // SelectorNode node;
  // ActionNode wander;
  // wander.action = []() { return kSuccess; };
  // node.children.emplace_back(&wander);

  const Villager villager{{0, 0}, {1, 1}, {32, 32}, 0};
  std::vector villagers{villager};

  graphics::Renderer renderer(1920, 1080, "City Builder", false);
  renderer.FirstRender(tiles, buildings, ui);
  while (renderer.Render()) {

  }
}

std::vector<citybuilder::game::Tile>
citybuilder::game::Game::GenerateRandomTiles() const {
  std::vector<Tile> tiles;
  fast_noise_lite noise;

  noise.SetSeed(random_generator_.Random(0, 10000));
  noise.SetNoiseType(fast_noise_lite::NoiseType_Perlin);
  noise.SetFrequency(0.01f);

  noise.SetFractalType(fast_noise_lite::FractalType_FBm);
  noise.SetFractalOctaves(4);
  noise.SetFractalLacunarity(0.7f);
  noise.SetFractalGain(0.15f);
  noise.SetFractalWeightedStrength(20);

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
      }

      tiles.emplace_back(tile);
    }
  }

  return tiles;
}