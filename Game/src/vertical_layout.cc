//
// Created by Kalle on 16.07.2026.
//

#include "placeables/vertical_layout.h"
void VerticalLayout::AddChild(const DisplayBox& child) {
  children_.push_back(child);
  LayoutChildren();
}

std::vector<DisplayBox>* VerticalLayout::GetChildren() { return &children_; }

void VerticalLayout::LayoutChildren() {
  const int ratio_y = display_box.size.y / static_cast<int>(children_.size());
  for (int i = 0; i < children_.size(); ++i) {
    auto& child = children_.at(i);
    child.position.x =
        display_box.position.x + display_box.size.x / 2 - child.size.x / 2;
    child.position.y = display_box.position.y + ratio_y * i + ratio_y / 2 - child.size.y / 2;
  }
}