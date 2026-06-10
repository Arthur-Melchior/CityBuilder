//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_BUILDING_H
#define CITYBUILDER_BUILDING_H

#include "placeable.h"

namespace citybuilder::game {

class Building {
 public:
  Vector2i position;
  Vector2i texture_coords;
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
