#include "element.hpp"

namespace wm
{
    
class TextBox : public RectangularElement
{
public:
    TextBox ();

    void setText(const std::string newText);

    virtual void onMouseDown(uint32_t x, uint32_t y);
    virtual void onTextEntered(uint32_t code);

private:
    sf::Font            font;
    sf::Text            text;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Window
{
public:
    Window(std::shared_ptr<sf::RenderWindow> renderWindow, std::shared_ptr<Element> child);

    void setFramePerSecond(int64_t framePerSecond);
    void start();

private:
    int64_t tickRate = 1000000 / 60;

    std::shared_ptr<sf::RenderWindow>   renderWindow;
    std::shared_ptr<Element>            child;
    sf::Clock                           clock;
    int64_t                             lastElaspedTime;

    void processEvents();
    void redraw();
};

}
