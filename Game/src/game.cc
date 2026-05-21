//
// Created by Kalle on 07.05.2026.
//

#include <game.h>
#include <tile.h>

#include <iostream>
#include <numeric>
#include <random>
#include <ranges>

#include "building.h"
#include "fast_noise_lite.h"
#include "renderer.h"

std::vector<citybuilder::game::Tile>
citybuilder::game::Game::GenerateRandomTiles() const {
  std::vector<Tile> tiles;
  fast_noise_lite noise;

  noise.SetSeed(1339);
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

      const std::array position = {static_cast<float>(i),
                                   static_cast<float>(j)};
      constexpr std::array<float, 2> texture_coords = {0, 0};

      Tile tile(position, texture_coords);

      if (noiseValue < -0.5f) {
        tile.texture_coords = {1, 1};
        tile.is_walkable = false;
      }

      tiles.emplace_back(tile);
    }
  }

  return tiles;
}

void citybuilder::game::Game::StartGame() const {
  const std::vector<Tile> tiles = GenerateRandomTiles();
  auto rng = RandomGenerator();

  Building b;
  b.position = {10, 10};
  b.size_x = 5;
  b.size_y = 2;

  int random_index = rng.random(0, tiles.size() - 1);
  auto tile = tiles[random_index];
  auto index =
      tile.position[1] - 1 + (tile.position[0] - 1) * world_size_width_;

  bool should_add = true;

  for (int i = 0; i < b.size_x; ++i) {
    if (!tiles[index + i].is_walkable) {
      should_add = false;
    }
  }

  graphics::Renderer renderer(800, 600, "City Builder");
  renderer.FirstRender(tiles);
}