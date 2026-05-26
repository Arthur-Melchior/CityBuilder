//
// Created by Arthur on 18.05.2026.
//

#ifndef CITYBUILDER_DISPLAY_BOX_H
#define CITYBUILDER_DISPLAY_BOX_H

#include <string>
#include "position_data.h"

namespace citybuilder::graphics {

class DisplayBox {
public:
  PositionData position_data;
  std::string text;
  unsigned int font_size = 30;
};

//position
//click event
//hover event
//color
//layer?

}  // namespace citybuilder::graphics

#endif  // CITYBUILDER_DISPLAY_BOX_H
