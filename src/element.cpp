#include "element.hpp"

namespace wm
{
    
RectangularElement::RectangularElement ()
{
    rect.setPosition(0, 0);
}
void RectangularElement::setSize(uint32_t width, uint32_t height)
{
    this->width=width;
    this->height=height;
    rect.setSize(sf::Vector2f(width, height));
}

uint32_t RectangularElement::getWidth() const { return width; }
uint32_t RectangularElement::getHeight() const { return height; }

}
