#include "core/drawable.hpp"

namespace core{

  void Drawable::setState( State status ){
    this->state = status;
  };
  void Drawable::setDrawTransformation(bool set) { 
    this->allowDrawTransformation = set;
  }
  bool Drawable::drawTransformation(){ 
    return this->allowDrawTransformation;
  }

  bool Drawable::needsDrawing( ){
    switch (state) {
      case State::NeedsDraw:
        return true;
      case State::NeedsUpdate:
        return true;
      default:
        return false;
    }
  }
}
