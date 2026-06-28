//
// Created by Arthur on 26.06.2026.
//

#ifndef CITYBUILDER_HORIZONTAL_LAYOUT_H
#define CITYBUILDER_HORIZONTAL_LAYOUT_H
#include <vector>

#include "display_box.h"

class HorizontalLayout {
 public:
  void AddChild(const DisplayBox& child);
  std::vector<DisplayBox>* GetChildren();
  DisplayBox display_box;

 private:
  std::vector<DisplayBox> children_;
  void LayoutChildren();
};

#endif  // CITYBUILDER_HORIZONTAL_LAYOUT_H
