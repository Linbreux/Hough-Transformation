#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "drawable.hpp"
#include <algorithm>
#include <iostream>
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
  void addDrawable( draw_sptr drawableToAdd ){
    this->drawables.push_back(std::move(drawableToAdd));
  }

  auto getDrawables() -> const std::vector<draw_sptr>& {
    return this->drawables;
  }

  auto getLastDrawable() -> std::weak_ptr<core::Drawable>{ 
    return this->drawables.empty() 
      ? std::weak_ptr<core::Drawable>()
      : this->drawables.at(this->drawables.size()-1);
  }

  auto redrawAll() -> void{
    for(auto drawing: drawables){
      drawing->setState(core::Drawable::State::NeedsDraw);
    }
  }

  auto removeType(core::Drawable::Type type){
    this->drawables.erase(
        std::remove_if(this->drawables.begin(), this->drawables.end(),
            [&](const std::shared_ptr<core::Drawable> obj) {
                if (obj->getType() == core::Drawable::Type::ReverseTransformPoint){
                  return true;
                }
                return false;
            }),
        this->drawables.end());
  }
};
} // namespace core

#endif // !COREMANAGER_H
