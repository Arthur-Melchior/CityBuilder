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
      std::array<float, 2> texture_coords = {0, 512};
      std::array position = {static_cast<float>(i), static_cast<float>(j)};
      tiles.emplace_back(position, texture_coords);
    }
  }

  graphics::Renderer renderer(800, 600, "City Builder");
  renderer.FirstRender(tiles);
}