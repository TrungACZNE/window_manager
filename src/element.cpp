#include "element.hpp"

namespace wm
{
    
RectangularElement::RectangularElement ()
{
    rect.setPosition(0, 0);
}
void RectangularElement::setSize(int width, int height)
{
    this->width=width;
    this->height=height;
    rect.setSize(sf::Vector2f(width, height));
}

int RectangularElement::getWidth() const { return width; }
int RectangularElement::getHeight() const { return height; }

}
