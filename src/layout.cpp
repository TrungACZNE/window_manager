#include "layout.hpp"

namespace wm
{
    
void LinearLayout::appendChild(std::shared_ptr<Element> window)
{
    children.push_back(window);
}

void LinearLayout::setColor(sf::Color color)
{
    rect.setFillColor(color);
}

HorizontalLayout::HorizontalLayout ()
{
    setColor(sf::Color::White);
}

void HorizontalLayout::onMouseDown(__attribute__ ((unused))int x, __attribute__ ((unused))int y)
{
}

void HorizontalLayout::onTextEntered(__attribute__ ((unused))uint32_t code)
{
}

void HorizontalLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int x = 0;
    target.draw(rect, states);
    for (auto child : children) {
        sf::RenderStates newStates = states;
        newStates.transform.translate(x, 0);
        target.draw(*child, newStates);
        x += child->getWidth();
    }
}


VerticalLayout::VerticalLayout ()
{
    setColor(sf::Color::White);
}

void VerticalLayout::onMouseDown(__attribute__ ((unused))int x, __attribute__ ((unused))int y)
{
}

void VerticalLayout::onTextEntered(__attribute__ ((unused))uint32_t code)
{
}

void VerticalLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int y = 0;
    target.draw(rect, states);
    for (auto child : children) {
        sf::RenderStates newStates = states;
        newStates.transform.translate(0, y);
        target.draw(*child, newStates);
        y += child->getHeight();
    }
}

}
