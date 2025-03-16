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

  Point(int x, int y, std::shared_ptr<Point> connectedTo = nullptr, int size = 1);

  auto setColor(std::string color) -> void;
  auto getColor() const -> std::optional<std::string>;

  void setType(Type type) override;
  auto getType() -> Type override;

  auto getX() const -> int;
  auto getY() const -> int;
  auto getSize() const -> int;
  auto doTransform() const -> std::vector<Transform::Hough::Polair>;

  auto getPoint() const -> std::tuple<int,int,int>;

  auto isConnected() const -> bool;
  auto getConnectedPoint() const -> std::weak_ptr<Point>;
};
} // namespace core

#endif // !COREPOINT_H
