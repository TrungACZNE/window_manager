#include "element.hpp"
namespace wm
{
    
class LinearLayout : public RectangularElement
{
public:
    void appendChild(std::shared_ptr<Element> window);
    void setColor(sf::Color color);

protected:
    std::vector<std::shared_ptr<Element> > children;
};

class HorizontalLayout : public LinearLayout
{
public:
    HorizontalLayout ();

    virtual void onMouseDown(__attribute__ ((unused))int x, __attribute__ ((unused))int y);
    virtual void onTextEntered(__attribute__ ((unused))uint32_t code);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class VerticalLayout : public LinearLayout
{
public:
    VerticalLayout ();

    virtual void onMouseDown(__attribute__ ((unused))int x, __attribute__ ((unused))int y);
    virtual void onTextEntered(__attribute__ ((unused))uint32_t code);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}
