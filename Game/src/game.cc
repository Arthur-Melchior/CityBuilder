//
// Created by Arthur on 07.05.2026.
//

#include <game.h>
#include <tile.h>

#include <random>
#include <ranges>

#include "building.h"
#include "fast_noise_lite.h"
#include "position_data.h"
#include "renderer.h"

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

      const Vector2f position = {static_cast<float>(i), static_cast<float>(j)};
      const Vector2f texture_coords = {3, 2};

      Tile tile(position, texture_coords);

      if (noiseValue < -0.5f) {
        tile.position_data.texture_coords = {7, 4};
        tile.is_walkable = false;
      }

      tiles.emplace_back(tile);
    }
  }

  return tiles;
}

void citybuilder::game::Game::StartGame() const {
  std::vector<Tile> tiles = GenerateRandomTiles();

  Building b{
      {{0, 0}, {5, 10}},
  };
  b.size_x = 5;
  b.size_y = 2;

  const int width = static_cast<int>(tiles.size()) / world_size_width_ - 1;
  const int height = static_cast<int>(tiles.size()) / world_size_height_ - 1;

  b.position_data.position = {
      static_cast<float>(random_generator_.Random(0, width)),
      static_cast<float>(random_generator_.Random(0, height))};
  while (!CanPlace(b, tiles, world_size_width_)) {
    b.position_data.position = {
        static_cast<float>(random_generator_.Random(0, width)),
        static_cast<float>(random_generator_.Random(0, height))};
  }

  Place(b, tiles, world_size_width_);
  std::vector buildings{b};

  DisplayBox test{{{0, 0}, {0, 0}}, {20, 20}};
  test.text = "test";

  std::vector ui{test};

  graphics::Renderer renderer(800, 600, "City Builder");
  renderer.FirstRender(tiles, buildings, ui);
}

template <HasPosition T>
bool citybuilder::game::Game::CanPlace(T object, const std::vector<Tile>& map,
                                       int map_width) const {
  const auto tile_index = object.position_data.position.x - 1 +
                          (object.position_data.position.y - 1) * map_width;

  for (int x = 0; x < object.size_x; ++x) {
    if (tile_index + x > map.size() - 1) {
      return false;
    }

    const auto x_index = x * map_width;

    for (int y = 0; y < object.size_y; ++y) {
      if (tile_index - y < 0 || !map[tile_index - y + x_index].is_walkable) {
        return false;
      }
    }
  }

  return true;
}

template <HasPosition T>
void citybuilder::game::Game::Place(T object, std::vector<Tile>& map,
                                    int map_width) const {
  const auto tile_index = object.position_data.position.x - 1 +
                          (object.position_data.position.y - 1) * map_width;

  for (int x = 0; x < object.size_x; ++x) {
    const auto x_index = x * map_width;

    for (int y = 0; y < object.size_y; ++y) {
      map[tile_index - y + x_index].is_walkable = false;
    }
  }
}