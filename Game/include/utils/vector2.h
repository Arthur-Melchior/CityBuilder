//
// Created by Kalle on 27.05.2026.
//

#ifndef CITYBUILDER_VECTOR2_H
#define CITYBUILDER_VECTOR2_H

template <typename T>
concept Number = requires(T a) { std::is_arithmetic_v<decltype(a)>; };

template <Number T>
struct Vector2 {
  Vector2(const T x, const T y) : x(x), y(y) {}

  auto operator<=>(const Vector2& v) const = default;

  T x = 0;
  T y = 0;

  T Distance(Vector2& target) noexcept {
    return std::abs(x - target.x) + std::abs(y - target.y);
  }
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

#endif  // CITYBUILDER_VECTOR2_H
