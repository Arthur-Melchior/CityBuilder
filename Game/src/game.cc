//
// Created by Kalle on 07.05.2026.
//

#include <game.h>
#include <tile.h>

#include "renderer.h"
void citybuilder::game::Game::StartGame() const {
  std::vector<Tile> tiles;

  for (int i = 0; i < number_tiles_width_; ++i) {
    for (int j = 0; j < number_tiles_height_; ++j) {
      std::array<float, 2> texture_coords = {0, 0};
      std::array position = {static_cast<float>(i), static_cast<float>(j)};
      tiles.emplace_back(position, texture_coords);
    }
  }

  tiles.emplace_back(std::array<float, 2>{200, 200}, std::array<float, 2>{1, 0});
  tiles.emplace_back(std::array<float, 2>{201, 201}, std::array<float, 2>{2, 0});
  tiles.emplace_back(std::array<float, 2>{202, 202}, std::array<float, 2>{0, 1});
  tiles.emplace_back(std::array<float, 2>{203, 203}, std::array<float, 2>{1, 1});
  tiles.emplace_back(std::array<float, 2>{204, 204}, std::array<float, 2>{2, 1});
  tiles.emplace_back(std::array<float, 2>{205, 205}, std::array<float, 2>{0, 2});
  tiles.emplace_back(std::array<float, 2>{206, 206}, std::array<float, 2>{1, 2});
  tiles.emplace_back(std::array<float, 2>{207, 207}, std::array<float, 2>{2, 2});

  graphics::Renderer renderer(800, 600, "City Builder");
  renderer.FirstRender(tiles);
}