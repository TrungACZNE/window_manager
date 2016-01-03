#include <stdint.h>

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>


namespace wm
{

class Window : public sf::RectangleShape
{
public:
    ~Window() { }
private:
};

class WindowManager
{
public:
    WindowManager(std::shared_ptr<sf::RenderWindow> renderWindow)
    {
        this->renderWindow = renderWindow;
        backgroundWindow.setPosition(0, 0);
        backgroundWindow.setSize(sf::Vector2f(800, 600));
        backgroundWindow.setFillColor(sf::Color::White);
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
    void bumpWindow(int index) {
        if (index == (int) windows.size() - 1) {
            return;
        }
        auto window = windows[index];
        windows.erase(windows.begin() + index);
        windows.push_back(window);
    }

    void processEvents() {
        sf::Event event;

        while (renderWindow->pollEvent(event))
        {
            int clicked;
            switch (event.type) {
                case sf::Event::Closed:
                    renderWindow->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    clicked = findEnclosingWindow(event.mouseButton.x, event.mouseButton.y) ;
                    if (clicked != -1) {
                        bumpWindow(clicked);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    std::cerr << "onMouseUp " << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
                    break;
                default:
                    break;

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
    window1->setSize(sf::Vector2f(500, 150));
    window1->setFillColor(sf::Color::Green);

    window2->setPosition(200, 200);
    window2->setSize(sf::Vector2f(500, 150));
    window2->setFillColor(sf::Color::Red);

    window3->setPosition(300, 300);
    window3->setSize(sf::Vector2f(500, 150));
    window3->setFillColor(sf::Color::Cyan);

    windowManager.start();
    return 0;
}