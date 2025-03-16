#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "drawable.hpp"

#include <memory>
#include <vector>

namespace core {
class Manager {
public:
  using draw_uptr = std::unique_ptr<Drawable>;
  using draw_wptr = std::weak_ptr<Drawable>;
  using draw_sptr = std::shared_ptr<Drawable>;

private:
  std::vector<draw_sptr> drawables;
public:
  /**
   *  Add a a drawable to the manager
   *  @param draw_sptr drawable pointer
   */
  void addDrawable( draw_sptr drawableToAdd );

  /**
   *  Get a const list of drawables. Can be used to draw objects.
   *  @return const std::vector<draw_sptr>& A list of drawables
   */
  auto getDrawables() -> const std::vector<draw_sptr>&;

  /**
   *  Get the last Drawable
   *  Usefull when needing previouse Drawable.
   *  eg. when drawing a line we need the previouse point
   *  @return std::weak_ptr<core::Drawable> the last drawable of the list
   **/
  auto getLastDrawable() -> std::weak_ptr<core::Drawable>;

  /**
   *  Redraw all objects.
   *  Sets the state to NeedsDraw.
   */
  void redrawAll();

  /**
   *  Remove a specific type from the managers drawables list.
   *  @param type The type to remove
   */
  void removeType(core::Drawable::Type type);

  /**
   *  Remove all drawables from the manager.
   */
  void removeAll();
};
} // namespace core

#endif // !COREMANAGER_H
