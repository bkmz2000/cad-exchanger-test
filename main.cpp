#include <iostream>
#include <vector>
#include <cstdlib>
#include <memory>
#include <algorithm>

#include "vector.h"
#include "shape.h"

const auto PI_OVER_4 = 3.14159265 / 4;

int main()
{
    std::vector<std::shared_ptr<Shape>> shapes;
    srand(time(0));

    int l = rand() % 1000;

    for (int i = 0; i < l; ++i)
    {
        int t = rand() % 3;
        if (t == 0)
        {
            float ra = rand() % 1000 + 1;
            float rb = rand() % 1000 + 1;

            shapes.push_back(std::make_shared<Ellipse>(Ellipse(ra, rb)));
        }

        if (t == 1)
        {
            float r = rand() % 1000 + 1;
            shapes.push_back(std::make_shared<Circle>(Circle(r)));
        }

        if (t == 2)
        {
            float r = rand() % 1000 + 1;
            shapes.push_back(std::make_shared<Helix>(Helix(r)));
        }
    }

    std::cout << "shapes: \n";
    for (auto sh : shapes)
    {
        auto circ = std::dynamic_pointer_cast<Circle>(sh);
        auto ellipse = std::dynamic_pointer_cast<Ellipse>(sh);
        auto helix = std::dynamic_pointer_cast<Helix>(sh);

        if (helix)
        {
            std::cout << *helix;
        }

        else if (circ)
        {
            std::cout << *circ;
        }

        else
        {
            std::cout << *ellipse;
        }

        std::cout << " "
                  << (*sh)(PI_OVER_4)
                  << " "
                  << sh->tang_at(PI_OVER_4)
                  << std::endl;
    }

    std::vector<std::shared_ptr<Shape>> circles;
    std::copy_if(shapes.begin(),
                 shapes.end(),
                 std::back_insert_iterator<std::vector<std::shared_ptr<Shape>>>(circles),
                 [](const std::shared_ptr<Shape> &sh)
                 {
                     if (!std::dynamic_pointer_cast<Helix>(sh) && std::dynamic_pointer_cast<Circle>(sh))
                     {
                         return true;
                     }
                     return false;
                 });

    std::cout << "\n\ncircles: \n";
    std::sort(circles.begin(),
              circles.end(),
              [](const std::shared_ptr<Shape> &a,
                 const std::shared_ptr<Shape> &b)
              {
                  auto ca = std::dynamic_pointer_cast<Circle>(a);
                  auto cb = std::dynamic_pointer_cast<Circle>(b);
                  return ca->get_ra() < cb->get_ra();
              });

    float total = 0;
    for (auto sh : circles)
    {
        auto circ = std::dynamic_pointer_cast<Circle>(sh);
        total += circ->get_ra();
        std::cout << *circ << std::endl;
    }

    std::cout << "total = " << total << std::endl;
    return 0;
}