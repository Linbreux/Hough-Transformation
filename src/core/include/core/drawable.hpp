#ifndef COREDRAWABLE_H
#define COREDRAWABLE_H

namespace core {
class Drawable {
public:
  enum class State{
    NeedsDraw,
    IsDrawn,
    NeedsUpdate,
  };

  enum class Type{
    Point,
    ReverseTransformPoint
  };

  State state { State::NeedsDraw };

public:
  virtual ~Drawable() = default;

  virtual auto setType(Drawable::Type type) -> void = 0;
  virtual Type getType() = 0;

  virtual void setState( State status ){
    this->state = status;
  };
  
  virtual void setDrawTransformation(bool set) { this->allowDrawTransformation = set;}
  virtual bool drawTransformation(){ return this->allowDrawTransformation; }

  virtual bool needsDrawing( ){
    switch (state) {
      case State::NeedsDraw:
        return true;
      case State::NeedsUpdate:
        return true;
      default:
        return false;
    }
  }
private:
  bool allowDrawTransformation{false};
};
} // namespace core

#endif // !COREDRAWABLE_H
