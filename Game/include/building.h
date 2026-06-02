//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_BUILDING_H
#define CITYBUILDER_BUILDING_H

#include "position_data.h"

namespace citybuilder::game {

class Building {
 public:
  PositionData position_data;
  Vector2f size;
};

// cost
// position
// output
// workers
// min workers
// max workers
// output modifier

}  // namespace citybuilder::game

#endif  // CITYBUILDER_BUILDING_H
