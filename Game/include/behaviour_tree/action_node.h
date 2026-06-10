//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_ACTION_NODE_H
#define CITYBUILDER_ACTION_NODE_H
#include <functional>

#include "behaviour_tree_node.h"

struct ActionNode : behaviour_tree_node {
  Status Tick() override { return action(); }
  std::function<Status()> action;
};

#endif  // CITYBUILDER_ACTION_NODE_H
