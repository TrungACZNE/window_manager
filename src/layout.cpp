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

void LinearLayout::onMouseDown(uint32_t x, uint32_t y)
{
    for (unsigned long i = 0; i < children.size(); ++i) {
        auto boundingBox = getChildBoundingBox(i);
        if (boundingBox.contains(x, y))
        {
            focusedChild = children[i];
            children[i]->onMouseDown(x - boundingBox.left, y - boundingBox.top);
            break;
        }
    }
}

void LinearLayout::onTextEntered(uint32_t code)
{
    auto focusedChild = getFocusedChild();
    if (focusedChild) focusedChild->onTextEntered(code);
}

std::shared_ptr<Element> LinearLayout::getFocusedChild()
{
    if (focusedChild) return focusedChild;
    else if (children.size() > 0) return children[0];
    else return std::shared_ptr<Element>();
}

void LinearLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rect, states);
    for (unsigned long i = 0; i < children.size(); ++i) {
        auto child = children[i];
        auto boundingBox = getChildBoundingBox(i);
        auto newStates = states;
        newStates.transform.translate(boundingBox.left, boundingBox.top);
        target.draw(*child, newStates);
    }
}

HorizontalLayout::HorizontalLayout ()
{
    setColor(sf::Color::White);
}

sf::Rect<uint32_t> HorizontalLayout::getChildBoundingBox(int childIndex) const
{
    uint32_t left = 0;
    for (int i = 0; i < childIndex; ++i) left += children[i]->getWidth();
    return sf::Rect<uint32_t>(left, 0, children[childIndex]->getWidth(), children[childIndex]->getHeight());
}

VerticalLayout::VerticalLayout ()
{
    setColor(sf::Color::White);
}

sf::Rect<uint32_t> VerticalLayout::getChildBoundingBox(int childIndex) const
{
    uint32_t top = 0;
    for (int i = 0; i < childIndex; ++i) top += children[i]->getHeight();
    return sf::Rect<uint32_t>(0, top, children[childIndex]->getWidth(), children[childIndex]->getHeight());
}

}
