#ifndef WM_ELEMENT_DEFINED
#define WM_ELEMENT_DEFINED

#include <stdint.h>

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

namespace wm
{

class Element : public sf::Drawable
{
public:
    virtual void setSize(int width, int height) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    virtual void onMouseDown(int x, int y) = 0;
    virtual void onTextEntered(uint32_t code) = 0;
};

class RectangularElement : public Element
{
public:
    RectangularElement ();
    virtual void setSize(int width, int height);

    virtual int getWidth() const;
    virtual int getHeight() const;

protected:
    int width, height;
    sf::RectangleShape  rect;
};
    
}

#endif
