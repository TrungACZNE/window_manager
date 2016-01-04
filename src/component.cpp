#include "component.hpp"

namespace wm
{

TextBox::TextBox()
{
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::Black);

    if (!font.loadFromFile("./data/fonts/monaco.ttf"))
    {
        throw "Cannot load font";
    }
    text.setPosition(0, 0);
    text.setFont(font);
    text.setCharacterSize(18);
    text.setColor(sf::Color::Black);
}

void TextBox::onMouseDown(uint32_t x, uint32_t y)
{
}

void TextBox::onTextEntered(uint32_t code)
{
    char c = (code < 128) ? static_cast<char>(code) : '?';
    text.setString(text.getString() + c);
}

void TextBox::setText(const std::string newText)
{
    text.setString(newText);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect, states);

    auto newStates = states;
    auto size = text.getLocalBounds();
    if (size.width < width) {
        newStates.transform.translate((width - size.width) / 2, 0 );
    }
    if (size.height < height) {
        newStates.transform.translate(0, (height - size.height) / 2);
    }
    target.draw(text, newStates);
}


Window::Window(std::shared_ptr<sf::RenderWindow> renderWindow, std::shared_ptr<Element> child)
{
    this->renderWindow = renderWindow;
    this->child = child;
}

void Window::setFramePerSecond(int64_t framePerSecond) {
    tickRate = 1000000 / framePerSecond;
}

void Window::processEvents() {
    sf::Event event;

    while (renderWindow->pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                renderWindow->close();
                break;
            case sf::Event::TextEntered:
                child->onTextEntered(event.text.unicode);
                break;
            case sf::Event::MouseButtonPressed:
                child->onMouseDown(event.mouseButton.x, event.mouseButton.y);
                break;
            default:
                break;
        }
    }
}

void Window::redraw() {
    renderWindow->clear();
    renderWindow->draw(*child);
    renderWindow->display();
}

void Window::start()
{
    clock.restart();
    lastElaspedTime = clock.getElapsedTime().asMicroseconds();

    while (renderWindow->isOpen())
    {
        int64_t currentElapsedTime = clock.getElapsedTime().asMicroseconds();
        int64_t timeDelta = currentElapsedTime - lastElaspedTime;
        if (timeDelta < tickRate) {
            sf::sleep(sf::microseconds(tickRate - timeDelta));
        } else {
            lastElaspedTime = currentElapsedTime;
            processEvents();
            redraw();
        }
    }
}

}
