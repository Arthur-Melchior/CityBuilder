//
// Created by Kalle on 07.05.2026.
//

#ifndef CITYBUILDER_GAME_H
#define CITYBUILDER_GAME_H
#include <complex.h>

#include <random>
#include <vector>

#include "random_generator.h"
#include "tile.h"

namespace citybuilder::game {

class Game {
 public:
  Game(const int world_size_width, const int world_size_height)
      : world_size_width_(world_size_width), world_size_height_(world_size_height) {}

  std::vector<Tile> GenerateRandomTiles() const;
  void StartGame() const;

 private:
  int world_size_width_;
  int world_size_height_;
  RandomGenerator random_generator_ = RandomGenerator();
};

// load title screen
// load main game
// save game
// villager milestones
// unlocking new buildings and resources
// game loop

}  // namespace citybuilder::game

#endif  // CITYBUILDER_GAME_H
