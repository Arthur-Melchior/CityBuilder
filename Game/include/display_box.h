//
// Created by Kalle on 27.05.2026.
//

#ifndef CITYBUILDER_DISPLAY_BOX_H
#define CITYBUILDER_DISPLAY_BOX_H
#include "placeable.h"

class DisplayBox {
public:
  Vector2i position;
  Vector2i texture_coords;
  Vector2f size;
  std::string text;
  unsigned int font_size = 30;
};

#endif  // CITYBUILDER_DISPLAY_BOX_H
