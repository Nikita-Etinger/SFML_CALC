#include "Button.h"
#include "Config.h"
#include <iostream>

Button::Button(std::string symbol,  sf::Color color_b, sf::Vector2f size, sf::Vector2f position, sf::Font& font)
    : symbol(symbol), color_b(color_b), font(font)
{
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(color_b);
    rectangle.setOutlineThickness(2); // толщина границы
    rectangle.setOutlineColor(sf::Color::Blue); // цвет границы

    buttonText.setFont(font);
    buttonText.setCharacterSize(FONT_SIZE);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString(sf::String(symbol));

    // Выравнивание текста по центру кнопки
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void Button::render(sf::RenderWindow& window)
{
    window.draw(rectangle);
    window.draw(buttonText);
}



std::string Button::update(sf::Vector2i mousePos, bool isMouseButtonPressed)
{
    std::string returnValue = ""; // Временная переменная для хранения результата

    bool isMouseOver = rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    if (isMouseOver)
    {
        if (isMouseButtonPressed && !hasBeenPressed)
        {
            hasBeenPressed = true;
            rectangle.setFillColor(sf::Color(80, 80, 80));
            returnValue = buttonText.getString(); // Сохранение значения в переменной
            
        }
        else if (!isMouseButtonPressed)
        {
            hasBeenPressed = false;
            rectangle.setFillColor(color_b);
        }
    }
    else
    {
        hasBeenPressed = false;
        rectangle.setFillColor(color_b);
    }

    return returnValue; 
} 

