//
// Created by Arthur on 07.05.2026.
//

#ifndef CITYBUILDER_GAME_H
#define CITYBUILDER_GAME_H

#include <random>
#include <vector>

#include "placeables/resource.h"
#include "placeables/tile.h"
#include "utils/random_generator.h"

namespace citybuilder::game {

class Game {
 public:
  Game(const int world_size_width, const int world_size_height)
      : world_size_width_(world_size_width),
        world_size_height_(world_size_height) {}

  void StartGame();
  [[nodiscard]] std::vector<Tile> GenerateRandomTiles(int seed);
  [[nodiscard]] std::vector<Resource> GenerateRandomResources(int seed) const;

  template <Placeable T>
  bool CanPlace(T& object, const std::vector<Tile>& map, int map_width) const {
    const auto tile_index =
        object.position.x - 1 + (object.position.y - 1) * map_width;

    for (int x = 0; x < object.size.x; ++x) {
      if (tile_index + x > map.size() - 1) {
        return false;
      }

      const auto x_index = x * map_width;

      for (int y = 0; y < object.size.y; ++y) {
        if (tile_index - y < 0 || !map[tile_index - y + x_index].is_walkable) {
          return false;
        }
      }
    }

    return true;
  }

  template <Placeable T>
  void Place(T& object, std::vector<Tile>& map, int map_width) const {
    const auto tile_index =
        object.position.x - 1 + (object.position.y - 1) * map_width;

    for (int x = 0; x < object.size.x; ++x) {
      const auto x_index = x * map_width;

      for (int y = 0; y < object.size.y; ++y) {
        map[tile_index - y + x_index].is_walkable = false;
      }
    }
  };

  Vector2i GetRandomWalkablePosition() const {
    auto x = random_generator_.Random(0, world_size_width_ - 1);
    auto y = random_generator_.Random(0, world_size_height_ - 1);

    while (!tiles_.at(x * world_size_width_ + y).is_walkable) {
      x = random_generator_.Random(0, world_size_width_ - 1);
      y = random_generator_.Random(0, world_size_height_ - 1);
    }

    return {x, y};
  }

  Vector2i GetClosestResourcePosition(Vector2i position,
                                      ResourceType resource_type) {
    Vector2i p{0,0};
    int distance = 10000;

    for (auto resource : resources_) {
      if (resource.resource_type == resource_type && resource.position.Distance(position) < distance) {
        p = resource.position;
      }
    }

    return p;
  }

 private:
  int world_size_width_;
  int world_size_height_;
  std::vector<Tile> tiles_;
  std::vector<Resource> resources_;
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
