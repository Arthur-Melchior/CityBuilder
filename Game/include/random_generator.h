//
// Created by Kalle on 21.05.2026.
//

#ifndef CITYBUILDER_RANDOM_GENERATOR_H
#define CITYBUILDER_RANDOM_GENERATOR_H
#include <random>

class RandomGenerator {
 public:
  RandomGenerator() : gen(std::random_device{}()) {}

  int random(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
  }

  float random(float min, float max) {
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
  }

  double random(double min, double max) {
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
  }

 private:
  std::mt19937 gen;
};

#endif  // CITYBUILDER_RANDOM_GENERATOR_H
