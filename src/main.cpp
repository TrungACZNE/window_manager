#include <stdint.h>

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>


namespace wm
{

class Window : public sf::Drawable
{
public:
    Window() throw (std::string)
    {
        rect.setFillColor(sf::Color::White);
        rect.setOutlineThickness(1);
        rect.setOutlineColor(sf::Color::Black);

        if (!font.loadFromFile("./data/fonts/monaco.ttf"))
        {
            throw "Cannot load font";
        }
        text.setFont(font);
        text.setCharacterSize(13);
        text.setColor(sf::Color::Black);
    }
    void onMouseDown(int x, int y)
    {
        std::cerr << "onMouseDown(" << x << ", " << y << ")" << std::endl;
    }

    void onTextEntered(uint32_t code)
    {
        char c = (code < 128) ? static_cast<char>(code) : '?';
        text.setString(text.getString() + c);
    }

    void setPosition(int x, int y)
    {
        this->x = x;
        this->y = y;
        updatePosition();
    }

    void setSize(int width, int height)
    {
        this->width=width;
        this->height=height;
        updateSize();
    }

    sf::FloatRect getGlobalBounds()	const
    {
        return rect.getGlobalBounds();
    }

    sf::FloatRect getLocalBounds() const
    {
        return rect.getLocalBounds();
    }

private:
    int x, y, width, height;
    sf::Font            font;
    sf::Text            text;
    sf::RectangleShape  rect;

    void updatePosition() {
        rect.setPosition(x, y);
        text.setPosition(x, y);
    }

    void updateSize() {
        rect.setSize(sf::Vector2f(width, height));
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(rect, states);
        target.draw(text, states);
    }
};

class WindowManager
{
public:
    WindowManager(std::shared_ptr<sf::RenderWindow> renderWindow)
    {
        this->renderWindow = renderWindow;
        backgroundWindow.setPosition(0, 0);
        backgroundWindow.setSize(800, 600);
    }

    int64_t tickRate = 1000000 / 60;

    void setFramePerSecond(int64_t framePerSecond) {
        tickRate = 1000000 / framePerSecond;
    }

    void appendChild(std::shared_ptr<wm::Window> window)
    {
        windows.push_back(window);
    }

    /* Return the index or -1 */
    int findEnclosingWindow(int x, int y)
    {
        for (int i = windows.size()-1; i >=0; --i) {
            if (windows[i]->getGlobalBounds().contains(x, y)) {
                return i;
            }
        }
        return -1;
    }

    /* bump a window to the top layer */
    void focusWindow(int index) {
        if (index == (int) windows.size() - 1) {
            return;
        }
        auto window = windows[index];
        windows.erase(windows.begin() + index);
        windows.push_back(window);
    }

    /* -1 if no window found */
    int getFocusedWindow()
    {
        return windows.size() - 1;
    }

    void processEvents() {
        sf::Event event;

        while (renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderWindow->close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int clicked = findEnclosingWindow(event.mouseButton.x, event.mouseButton.y);
                if (clicked != -1) {
                    focusWindow(clicked);
                }
                break;
            }

            int focusedIndex = getFocusedWindow();
            if (focusedIndex != - 1) {
                auto window = windows[focusedIndex];
                auto bounds = window->getLocalBounds();
                switch (event.type)
                {
                    case sf::Event::MouseButtonPressed:
                        window->onMouseDown(event.mouseButton.x - bounds.left, event.mouseButton.y - bounds.top);
                        break;
                    case sf::Event::TextEntered:
                        window->onTextEntered(event.text.unicode);
                        break;
                    default: break;
                }
            }
        }
    }

    void redraw() {
        renderWindow->clear();
        renderWindow->draw(backgroundWindow);
        for (auto w : windows) {
            renderWindow->draw(*w);
        }
        renderWindow->display();
    }

    void start()
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

private:
    /* sorted by z-index */
    std::vector<std::shared_ptr<wm::Window> >   windows;
    wm::Window                                  backgroundWindow;

    std::shared_ptr<sf::RenderWindow> renderWindow;
    sf::Clock                   clock;
    int64_t                     lastElaspedTime;
};

}

int main()
{
    std::ios_base::sync_with_stdio(false);

    wm::WindowManager windowManager(std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!")));

    std::shared_ptr<wm::Window>
        window1(new wm::Window()),
        window2(new wm::Window()),
        window3(new wm::Window());
    windowManager.appendChild(window1);
    windowManager.appendChild(window2);
    windowManager.appendChild(window3);

    window1->setPosition(100, 100);
    window1->setSize(500, 150);

    window2->setPosition(200, 200);
    window2->setSize(500, 150);

    window3->setPosition(100, 300);
    window3->setSize(600, 100);

    windowManager.start();
    return 0;
}
