#include "core/point.hpp"

namespace core{
  Point::Point(int x, int y, std::shared_ptr<Point> connectedTo, int size)
    : x(x)
    , y(y)
    , connectedPoint(connectedTo)
    , size(size)
  {
  };

  auto Point::setColor(std::string color) -> void {
    this->color = color;
  }

  auto Point::getColor() const -> std::optional<std::string> {
    return this->color;
  }

  auto Point::getType() -> Type { 
    return this->type; 
  }
  void Point::setType(Drawable::Type type) {
    this->type = type;
  }

  auto Point::getX() const -> int { return this->x; };
  auto Point::getY() const -> int { return this->y; };
  auto Point::getSize() const -> int { return this->size; }
  auto Point::doTransform() const -> std::vector<Transform::Hough::Polair> {
    return Transform::Hough::transformFromCartesian(this->x, this->y);
  }

  auto Point::getPoint() const -> std::tuple<int,int,int> {
    return std::make_tuple(this->x, this->y, this->size);
  }

  auto Point::isConnected() const -> bool {
    return !this->connectedPoint.expired();
  }

  auto Point::getConnectedPoint() const -> std::weak_ptr<Point> {
    return this->connectedPoint;
  }
}
