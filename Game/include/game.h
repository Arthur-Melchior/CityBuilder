//
// Created by Kalle on 07.05.2026.
//

#ifndef CITYBUILDER_GAME_H
#define CITYBUILDER_GAME_H

namespace citybuilder::game {

class Game {
 public:
  Game(const int ntw, const int nth)
      : number_tiles_width_(ntw), number_tiles_height_(nth) {}

  void StartGame() const;

 private:
  int number_tiles_width_;
  int number_tiles_height_;
};

// load title screen
// load main game
// save game
// villager milestones
// unlocking new buildings and resources
// game loop

}  // namespace citybuilder::game

#endif  // CITYBUILDER_GAME_H
