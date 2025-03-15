#include <cstddef>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>

namespace Transform{
  class Hough{
    public:
    struct Polair{
      float r{0};
      float angle{0};
    };
    public:
      static std::vector<Polair> transformFromCartesian(int x, int y){
          uint amountOfPoints = 180;
          std::vector<Polair> transformation(amountOfPoints);
          for (float angle=0; angle<amountOfPoints; angle+=0.5){
            //calculate
            float r = x * cos(angle*3.1415/180) + y*sin(angle*3.1414/180);

            transformation.push_back(Polair{r, angle});
          }
          return transformation;
      }

      static std::vector<std::pair<int,int>> transformToCartesian(Polair p){
          std::vector<std::pair<int,int>> transformation;
          float x1 = 0;
          float y1 = (p.r - x1*cos(p.angle*3.1425/180))/sin(p.angle*3.1415/180);
          transformation.push_back(std::pair<int,int>(x1, y1));

          float x2 = 2000;
          float y2 = (p.r - x2*cos(p.angle*3.1425/180))/sin(p.angle*3.1415/180);
          transformation.push_back(std::pair<int,int>(x2, y2));

          return transformation;
      }
  };
}
