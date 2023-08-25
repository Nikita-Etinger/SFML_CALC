#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.h"
#include "Button.h"


class App
{
private:
    std::map<char, int> PRIORITY = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
    std::vector<Button> keyBoards;
    const std::string symbols[19] = {
        "AC","+/-","%","/","7","8","9","X","4","5","6","-","1","2","3","+","0",".","="
    };
    sf::Font font;
    sf::Text resultText;
    bool pointEntered = false;

public:
    
    float eExpression();
    void update(sf::RenderWindow& window);
    void actions(std::string buttonSymbol);
    float calculate(float operand1, char op, float operand2);
    void run();
};

