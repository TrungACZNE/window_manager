#include "element.hpp"
namespace wm
{
    
class LinearLayout : public RectangularElement
{
public:
    void appendChild(std::shared_ptr<Element> window);
    void setColor(sf::Color color);

    virtual void onMouseDown(uint32_t x, uint32_t y);
    virtual void onTextEntered(uint32_t code);

protected:
    std::vector<std::shared_ptr<Element> >  children;
    std::shared_ptr<Element>                focusedChild;

private:
    std::shared_ptr<Element> getFocusedChild();
    virtual sf::Rect<uint32_t> getChildBoundingBox(int childIndex) const = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class HorizontalLayout : public LinearLayout
{
public:
    HorizontalLayout ();

private:
    virtual sf::Rect<uint32_t> getChildBoundingBox(int childIndex) const;
};

class VerticalLayout : public LinearLayout
{
public:
    VerticalLayout ();

private:
    virtual sf::Rect<uint32_t> getChildBoundingBox(int childIndex) const;
};

}
