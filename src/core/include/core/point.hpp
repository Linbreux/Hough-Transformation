#ifndef COREPOINT_H
#define COREPOINT_H

#include <memory>
#include <optional>
#include <tuple>

#include <iostream>

#include "drawable.hpp"
#include <core/transform.hpp>

namespace core {

class Point : public Drawable {
private:
    int x;
    int y;
    int size;
    std::weak_ptr<Point> connectedPoint;
    std::optional<std::string> color;

    Drawable::Type type = Drawable::Type::Point;
    
public:
  Point(const Point &) = default;
  Point(Point &&) = default;
  Point &operator=(const Point &) = default;
  Point &operator=(Point &&) = default;

  Point(int x, int y, std::shared_ptr<Point> connectedTo = nullptr, int size = 1)
    : x(x)
    , y(y)
    , connectedPoint(connectedTo)
    , size(size)
  {
  };

  auto setColor(std::string color) -> void {
    this->color = color;
  }

  auto getColor() -> std::optional<std::string> {
    return this->color;
  }

  auto getType() -> Drawable::Type override { return this->type; }
  auto setType(Drawable::Type type) -> void override { this->type = type; }

  auto getX() -> int { return this->x; };
  auto getY() -> int { return this->y; };
  auto getSize() -> int { return this->size; }
  auto doTransform() -> std::vector<Transform::Hough::Polair> { return Transform::Hough::transformFromCartesian(this->x, this->y);}

  auto getPoint() -> std::tuple<int,int,int> { return std::make_tuple(this->x, this->y, this->size);}

  auto isConnected() -> bool {return !this->connectedPoint.expired(); }
  auto getConnectedPoint() -> std::weak_ptr<Point> { return this->connectedPoint; }
};
} // namespace core

#endif // !COREPOINT_H
