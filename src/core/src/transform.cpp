#include "core/transform.hpp"

namespace Transform{

      auto Hough::transformFromCartesian(int x, int y) -> std::vector<Polair>{
          uint amountOfPoints = 360;
          std::vector<Polair> transformation(amountOfPoints);
          for (float angle=0; angle<amountOfPoints; angle+=0.5){
            //calculate
            float r = x * cos(angle*3.1415/180) + y*sin(angle*3.1414/180);

            transformation.push_back(Polair{r, angle});
          }
          return transformation;
      }

      auto Hough::transformToCartesian(Polair p) -> std::vector<std::pair<int,int>> {
          std::vector<std::pair<int,int>> transformation;
          float x1 = 0;
          float y1 = (p.r - x1*cos(p.angle*3.1425/180))/sin(p.angle*3.1415/180);
          transformation.push_back(std::pair<int,int>(x1, y1));

          float x2 = 2000;
          float y2 = (p.r - x2*cos(p.angle*3.1425/180))/sin(p.angle*3.1415/180);
          transformation.push_back(std::pair<int,int>(x2, y2));

          return transformation;
      }
}
