//
// Created by Arthur on 07.05.2026.
//

#ifndef CITYBUILDER_GAME_H
#define CITYBUILDER_GAME_H

#include <random>
#include <vector>

#include "random_generator.h"
#include "tile.h"

namespace citybuilder::game {

class Game {
 public:
  Game(const int world_size_width, const int world_size_height)
      : world_size_width_(world_size_width),
        world_size_height_(world_size_height) {}

  void StartGame() const;
  [[nodiscard]] std::vector<Tile> GenerateRandomTiles() const;

  template <HasPosition T>
  bool CanPlace(T object, const std::vector<Tile>& map, int map_width) const;

  template <HasPosition T>
  void Place(T object, std::vector<Tile>& map, int map_width) const;

 private:
  int world_size_width_;
  int world_size_height_;
  RandomGenerator random_generator_{};
};

// load title screen
// load main game
// save game
// villager milestones
// unlocking new buildings and resources
// game loop

}  // namespace citybuilder::game

#endif  // CITYBUILDER_GAME_H
