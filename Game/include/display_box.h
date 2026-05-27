//
// Created by Kalle on 27.05.2026.
//

#ifndef CITYBUILDER_DISPLAY_BOX_H
#define CITYBUILDER_DISPLAY_BOX_H
#include "position_data.h"

class DisplayBox {
public:
  PositionData position_data;
  Vector2f size;
  std::string text;
  unsigned int font_size = 30;
};

#endif  // CITYBUILDER_DISPLAY_BOX_H
