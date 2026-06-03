//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_SELECTOR_NODE_H
#define CITYBUILDER_SELECTOR_NODE_H
#include "node.h"

struct SelectorNode : Node {
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
};

#endif  // CITYBUILDER_SELECTOR_NODE_H
