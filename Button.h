#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    std::string symbol;
    sf::Color color_b;
    sf::RectangleShape rectangle;
    sf::Text buttonText; 
    sf::Font& font;
    bool hasBeenPressed = false;

public:
    Button(std::string symbol,  sf::Color color_b, sf::Vector2f size, sf::Vector2f position, sf::Font& font);
    void render(sf::RenderWindow& window);
    std::string update(sf::Vector2i mousePos, bool isMouseButtonPressed);
};