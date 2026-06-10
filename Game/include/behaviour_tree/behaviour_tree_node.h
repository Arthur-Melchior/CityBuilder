//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_BEHAVIOURTREENODE_H
#define CITYBUILDER_BEHAVIOURTREENODE_H
#include <vector>

enum Status {
  kFailure,
  kSuccess,
  kRunning,
};

struct  behaviour_tree_node {
  virtual ~behaviour_tree_node() = default;
  virtual Status Tick();

  behaviour_tree_node(behaviour_tree_node&& node) noexcept{
    std::swap(status, node.status);
  }
  behaviour_tree_node& operator=(behaviour_tree_node&& node) noexcept {
    std::swap(status, node.status);
    return *this;
  }

  Status status = kFailure;
};

#endif  // CITYBUILDER_BEHAVIOURTREENODE_H
