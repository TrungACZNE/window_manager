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
    virtual void setSize(uint32_t width, uint32_t height) = 0;
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    virtual void onMouseDown(uint32_t x, uint32_t y) = 0;
    virtual void onTextEntered(uint32_t code) = 0;
};

class RectangularElement : public Element
{
public:
    RectangularElement ();
    virtual void setSize(uint32_t width, uint32_t height);

    virtual uint32_t getWidth() const;
    virtual uint32_t getHeight() const;

protected:
    uint32_t width, height;
    sf::RectangleShape  rect;
};
    
}

#endif
