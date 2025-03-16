#include "core/manager.hpp"
#include "core/drawable.hpp"

#include <algorithm>

namespace core{
  void Manager::addDrawable( draw_sptr drawableToAdd ){
    this->drawables.push_back(std::move(drawableToAdd));
  }

  auto Manager::getDrawables() -> const std::vector<draw_sptr>& {
    return this->drawables;
  }

  auto Manager::getLastDrawable() -> std::weak_ptr<Drawable>{ 
    return this->drawables.empty() 
      ? std::weak_ptr<core::Drawable>()
      : this->drawables.at(this->drawables.size()-1);
  }

  auto Manager::redrawAll() -> void{
    for(auto drawing: drawables){
      drawing->setState(core::Drawable::State::NeedsDraw);
    }
  }

  void Manager::removeType(Drawable::Type type){
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

  void Manager::removeAll(){
    this->drawables.clear();
  }
}
