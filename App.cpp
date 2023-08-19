#include "App.h"
#include <iostream>

void App::calculate()
{


}

void App::update(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (Button& button : keyBoards)
    {
       actions( button.update(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left)));
    }
}

void App::actions(std::string buttonSymbol)
{
    if (buttonSymbol == "=") {
        calculate();
    }
    else if (buttonSymbol == "AC") {
        resultText.setString("");
    }
    else if (buttonSymbol == ".") {
        std::string str = resultText.getString();
        bool flagOpperand = 0;
        bool flagSymbol = 0;
        bool flagPoint = 0;
        for (int i = 0; i < str.length(); i++) {

            if (str[i] == '.') {
                flagPoint = 1;
                break;
            }

        }
        if (flagPoint == 0) {
            resultText.setString(resultText.getString() + buttonSymbol);
        }
    }
    else {
        resultText.setString(resultText.getString() + buttonSymbol);
    }
    
}


void App::run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Button App");
    font.loadFromFile("arial.ttf");
    resultText.setFillColor(sf::Color::Red);
    resultText.setFont(font);

    for (int row = 0, symbolIndex=0; row < 5; ++row) {
        for (int i = 0; i < 4; ++i) {
            if (symbolIndex < 19) {
                sf::Vector2f buttonPosition;
                buttonPosition.x = (symbolIndex == 18) ? BUTTON_SIZE * 3 : i * (BUTTON_SIZE * ((symbolIndex == 17) ? 2 : 1));
                buttonPosition.y = row * BUTTON_SIZE+ BUTTON_SIZE;

                sf::Vector2f buttonSize(BUTTON_SIZE * ((symbolIndex == 16) ? 2 : 1), BUTTON_SIZE);

                Button button(symbols[symbolIndex],(i!=3&&symbolIndex!=18)? sf::Color::White: sf::Color::Color(255, 165, 0), buttonSize, buttonPosition, font);
                keyBoards.push_back(button);
            }
            symbolIndex++;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        update(window);
        window.clear();

        for (Button& button : keyBoards)
        {
            button.render(window);
        }
        
        resultText.setPosition(BUTTON_SIZE * 4 - resultText.getGlobalBounds().width, BUTTON_SIZE / 3);
        window.draw(resultText);
        window.display();
    }
}