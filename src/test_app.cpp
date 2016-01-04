#include "layout.hpp"
#include "component.hpp"

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::shared_ptr<wm::VerticalLayout> col1(new wm::VerticalLayout);
    col1->setSize(400, 600);

    std::shared_ptr<wm::TextBox> textbox11(new wm::TextBox);
    textbox11->setSize(400, 100);

    std::shared_ptr<wm::HorizontalLayout> row12(new wm::HorizontalLayout);
    row12->setSize(400, 400);
    std::shared_ptr<wm::TextBox> textbox121(new wm::TextBox);
    textbox121->setSize(150, 400);
    textbox121->setText("Hello world");

    std::shared_ptr<wm::TextBox> textbox122(new wm::TextBox);
    textbox122->setSize(150, 400);
    textbox122->setText("1+1=2");

    std::shared_ptr<wm::TextBox> textbox123(new wm::TextBox);
    textbox123->setSize(100, 400);
    textbox123->setText("LOREM IPSUM");

    row12->appendChild(textbox121);
    row12->appendChild(textbox122);
    row12->appendChild(textbox123);

    std::shared_ptr<wm::TextBox> textbox13(new wm::TextBox);
    textbox13->setSize(400, 100);

    col1->appendChild(textbox11);
    col1->appendChild(row12);
    col1->appendChild(textbox13);

    std::shared_ptr<wm::VerticalLayout> col2(new wm::VerticalLayout);
    col2->setSize(400, 600);

    std::shared_ptr<wm::TextBox> textbox21(new wm::TextBox);
    textbox21->setSize(400, 200);
    textbox21->setText("So");

    std::shared_ptr<wm::TextBox> textbox22(new wm::TextBox);
    textbox22->setSize(400, 400);
    textbox22->setText("Here I am");

    col2->appendChild(textbox21);
    col2->appendChild(textbox22);

    std::shared_ptr<wm::HorizontalLayout> root(new wm::HorizontalLayout);
    root->setSize(800, 600);
    root->appendChild(col1);
    root->appendChild(col2);

    wm::Window windowManager(std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!")), root);

    windowManager.start();

}
