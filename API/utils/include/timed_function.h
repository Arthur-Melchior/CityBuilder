//
// Created by Kalle on 04.06.2026.
//

#ifndef CITYBUILDER_TIMED_FUNCTION_H
#define CITYBUILDER_TIMED_FUNCTION_H

#include <functional>
#include <variant>

#include "vector2.h"

class TimedFunction {
 public:
  std::function<std::any> function;
  float repeat_rate = 0;

  template<typename Func, typename... Args>
  void SetFunction(Func&& f, Args&&... args) {
    function = std::bind(std::forward<Func>(f), std::forward<Args>(args)...);
  }

  void Tick(const float elapsed_time) {
    delta_time_ += elapsed_time;
    if (delta_time_ >= repeat_rate) {
      function();
      delta_time_ = 0;
    }
  };

 private:
  float delta_time_ = 0;
};

using AnyTimedFunction =
    std::variant<TimedFunction<int()>, TimedFunction<void()>,
                 TimedFunction<int(int)>, TimedFunction<Vector2<>>>;

#endif  // CITYBUILDER_TIMED_FUNCTION_H
