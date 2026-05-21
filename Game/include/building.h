//
// Created by Kalle on 18.05.2026.
//

#ifndef CITYBUILDER_BUILDING_H
#define CITYBUILDER_BUILDING_H
#include <array>

namespace citybuilder::game {

class Building {
public:
  std::array<int,2> position;
  int size_x;
  int size_y;
};

//cost
//position
//output
//workers
//min workers
//max workers
//output modifier

} // namespace citybuilder::game

#endif  // CITYBUILDER_BUILDING_H
