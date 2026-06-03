//
// Created by Kalle on 03.06.2026.
//

#ifndef CITYBUILDER_NODE_H
#define CITYBUILDER_NODE_H
#include <vector>

enum Status {
  kFailure,
  kSuccess,
  kRunning,
};

struct  Node {
  virtual ~Node() = default;
  virtual Status Tick();
  std::vector<Node*> children;
  Status status;
};

#endif  // CITYBUILDER_NODE_H
