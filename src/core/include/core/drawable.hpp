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

  // ------- Pure virtual functions 
  /**
   *  Set the type of the Drawable
   *  eg. Point, ReverseTransformPoint, ...
   *  @param type the type to set
   */
  virtual auto setType(Drawable::Type type) -> void = 0;

  /**
   *  Get the type of the Drawable
   *  eg. Point, ReverseTransformPoint, ...
   *  @return Drawable::Type
   */
  virtual auto getType() -> Type = 0;

  // ------- Virtual functions
  /**
   *  Set the state, eg. NeedsDraw, IsDrawn, ...
   *  @param status The status the object should get.
   */
  virtual void setState( State status );

  /**
   *  Does the drawable needs to be drawn on the transformation
   *  if set, the Drawable will be also be projected on the transformation
   *  screen.
   *  @param set Value to set
   */
  virtual void setDrawTransformation(bool set);

  /**
   *  Does the drawable needs to be drawn on the transformation
   *  screen?
   *  @return bool Draw transformation?
   */
  virtual auto drawTransformation() -> bool;

  /**
   *  Is a redraw needed?
   *  @return bool Should we redraw?
   */
  virtual auto needsDrawing() -> bool;

private:
  bool allowDrawTransformation{false};
};
} // namespace core

#endif // !COREDRAWABLE_H
