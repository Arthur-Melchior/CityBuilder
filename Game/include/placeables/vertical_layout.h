//
// Created by Kalle on 16.07.2026.
//

#ifndef CITYBUILDER_VERTICAL_LAYOUT_H
#define CITYBUILDER_VERTICAL_LAYOUT_H
#include "display_box.h"

class VerticalLayout {
public:
  void AddChild(const DisplayBox& child);
  std::vector<DisplayBox>* GetChildren();
  DisplayBox display_box;

private:
  std::vector<DisplayBox> children_;
  void LayoutChildren();
};

#endif  // CITYBUILDER_VERTICAL_LAYOUT_H
