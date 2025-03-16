#ifndef CORETRANSFORM_H
#define CORETRANSFORM_H
#include <utility>
#include <vector>
#include <cmath>

namespace Transform{
  class Hough{
    public:
    struct Polair{
      float r{0};
      float angle{0};
    };
    public:
      static auto transformFromCartesian(int x, int y) -> std::vector<Polair>;
      static auto transformToCartesian(Polair p) -> std::vector<std::pair<int,int>>;
  };
}
#endif
