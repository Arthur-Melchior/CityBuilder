//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_SEQUENCE_NODE_H
#define CITYBUILDER_SEQUENCE_NODE_H
#include "node.h"

struct SequenceNode : Node {
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
  std::vector<Node*> children;
};

#endif  // CITYBUILDER_SEQUENCE_NODE_H
