//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_SELECTOR_NODE_H
#define CITYBUILDER_SELECTOR_NODE_H
#include <queue>

#include "behaviour_tree_node.h"

struct SelectorNode : behaviour_tree_node {
  Status Tick() override {
    const auto status = children[currentChild]->Tick();

    if (status == kFailure) {
      currentChild++;

      if (currentChild >= children.size()) {
        currentChild = 0;
        return kFailure;
      }

      return Tick();
    }

    return status;
  }

  int currentChild = 0;
  std::vector<behaviour_tree_node*> children;
};

#endif  // CITYBUILDER_SELECTOR_NODE_H
