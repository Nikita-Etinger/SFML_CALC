#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.h"
#include "Button.h"
#include <string>

class App
{
private:
    std::vector<Button> keyBoards;
    const std::string symbols[19] = {
        "AC","+/-","%","/","7","8","9","X","4","5","6","-","1","2","3","+","0",".","="
    };
    sf::Font font;
    sf::Text resultText;
    

public:
    void calculate();
    void update(sf::RenderWindow& window);
    void actions(std::string buttonSymbol);
    void run();
};

