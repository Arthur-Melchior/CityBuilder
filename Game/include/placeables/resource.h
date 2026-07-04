//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_RESOURCE_H
#define CITYBUILDER_RESOURCE_H
#include "utils/vector2.h"

namespace citybuilder::game {

class Resource {
public:
  std::string name;
  Vector2i position;
  Vector2i texture_coords;
  Vector2i size{1, 1};
};
//how to make it (if it can be made)
//position
//base price
//market modifier
//texture coordinates
//gathered texture coordinates

} // namespace citybuilder::game

#endif  // CITYBUILDER_RESOURCE_H
