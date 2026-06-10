//
// Created by Arthur on 21.05.2026.
//

#ifndef CITYBUILDER_RANDOM_GENERATOR_H
#define CITYBUILDER_RANDOM_GENERATOR_H
#include <random>

class RandomGenerator {
 public:
  RandomGenerator() : gen(std::random_device{}()) {}

  int Random(const int min, const int max) const {
    std::uniform_int_distribution distrib(min, max);
    return distrib(gen);
  }

  float Random(const float min, const float max) const {
    std::uniform_real_distribution distrib(min, max);
    return distrib(gen);
  }

  double Random(const double min, const double max) const {
    std::uniform_real_distribution distrib(min, max);
    return distrib(gen);
  }

 private:
  mutable std::mt19937 gen;
};

#endif  // CITYBUILDER_RANDOM_GENERATOR_H
