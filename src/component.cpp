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
    text.setCharacterSize(13);
    text.setColor(sf::Color::Black);
}

void TextBox::onMouseDown(int x, int y)
{
    std::cerr << "onMouseDown(" << x << ", " << y << ")" << std::endl;
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
    target.draw(text, states);
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
        if (event.type == sf::Event::Closed)
        {
            renderWindow->close();
            return;
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