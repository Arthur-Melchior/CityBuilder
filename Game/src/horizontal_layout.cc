//
// Created by Arthur on 26.06.2026.
//

#include "placeables/horizontal_layout.h"

void HorizontalLayout::AddChild(const DisplayBox& child) {
  children_.push_back(child);
  LayoutChildren();
}

std::vector<DisplayBox>* HorizontalLayout::GetChildren() { return &children_; }

void HorizontalLayout::LayoutChildren() {
  const int ratio_x = display_box.size.x / static_cast<int>(children_.size());
  const int y_position = display_box.position.y + display_box.size.y / 2;
  for (int i = 0; i < children_.size(); ++i) {
    auto& child = children_.at(i);
    child.position.x =
        i * ratio_x + ratio_x / 2 + display_box.position.x - child.size.x / 2;
    child.position.y = y_position - child.size.y / 2;
  }
}