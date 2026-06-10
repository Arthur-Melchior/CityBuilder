//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_SEQUENCE_NODE_H
#define CITYBUILDER_SEQUENCE_NODE_H
#include "behaviour_tree_node.h"

struct SequenceNode : behaviour_tree_node {
  Status Tick() override {
    const auto status = children[current_child]->Tick();

    if (status == kSuccess) {
      current_child++;

      if (current_child >= children.size()) {
        current_child = 0;
        return kSuccess;
      }

      return Tick();
    }
    return status;
  }
  int current_child = 0;
  std::vector<behaviour_tree_node*> children;
};

#endif  // CITYBUILDER_SEQUENCE_NODE_H
