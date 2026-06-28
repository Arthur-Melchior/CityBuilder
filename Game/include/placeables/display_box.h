//
// Created by Kalle on 27.05.2026.
//

#ifndef CITYBUILDER_DISPLAY_BOX_H
#define CITYBUILDER_DISPLAY_BOX_H
#include "placeable.h"
#include <string>

class DisplayBox {
 public:
  Vector2i position = {0, 0};
  Vector2i texture_coords = {0, 0};
  Vector2i size = {0, 0};
  std::string text;
  unsigned int font_size = 30;
  bool is_button = false;
};

#endif  // CITYBUILDER_DISPLAY_BOX_H
