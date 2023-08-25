#include "App.h"
#include <iostream>


// Функция для вычисления значения выражения
float App::eExpression() {
    std::string expression = resultText.getString();
    std::stack<float> operandStack;      // Стек для операндов
    std::stack<char> operatorStack;      // Стек для операторов

    for (size_t i = 0; i < expression.size(); ++i) {
        char ch = expression[i];

        if (isdigit(ch) || ch == '.') {  // Если символ - цифра или точка (часть числа)
            std::string numStr;
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {//isdigit-проверка на цифру
                numStr += expression[i];
                ++i;
            }
            --i; // Вернуться на последний валидный символ
            operandStack.push(stof(numStr));  // Преобразование строки в число с плавающей точкой и добавление в стек операндов
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {  // Если символ - оператор
            while (!operatorStack.empty() && PRIORITY[ch] <= PRIORITY[ operatorStack.top()]) {
                char op = operatorStack.top();
                operatorStack.pop();
                float operand2 = operandStack.top();
                operandStack.pop();
                float operand1 = operandStack.top();
                operandStack.pop();
                float result = calculate(operand1, op, operand2);  // Выполнение операции над операндами
                operandStack.push(result);  // Добавление результата в стек операндов
            }
            operatorStack.push(ch);  // Добавление оператора в стек операторов
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();
        float operand2 = operandStack.top();
        operandStack.pop();
        float operand1 = operandStack.top();
        operandStack.pop();
        float result = calculate(operand1, op, operand2);  // Выполнение оставшейся операции
        operandStack.push(result);  // Добавление результата в стек операндов
    }
    return operandStack.top();  // Возврат результата вычислений
}





void App::update(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (Button& button : keyBoards)
    {
       actions( button.update(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left)));
    }
}

void App::actions(std::string buttonSymbol) {
    if (buttonSymbol == "=") {
        resultText.setString(std::to_string(eExpression()));
    }
    else if (buttonSymbol == "AC") {
        resultText.setString("");
        pointEntered = false; // Сброс флага при очистке
    }
    else if (buttonSymbol == ".") {
        if (!pointEntered) {
            // Добавляем точку, но предварительно проверяем наличие оператора перед ней
            std::string str = resultText.getString();
            if (str.empty() || str.back() == '+' || str.back() == '-' || str.back() == '*' || str.back() == '/') {
                resultText.setString(resultText.getString() + "0" + buttonSymbol);
            }
            else {
                resultText.setString(resultText.getString() + buttonSymbol);
            }
            pointEntered = true;
        }
    }
    else if (buttonSymbol == "+" || buttonSymbol == "-" || buttonSymbol == "*" || buttonSymbol == "/") {
        pointEntered = false; // Сброс флага при вводе оператора
        resultText.setString(resultText.getString() + buttonSymbol);
    }
    else {
        resultText.setString(resultText.getString() + buttonSymbol);
    }
}
float App::calculate(float operand1, char op, float operand2)
{
    switch (op) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    default:
        return 0.0;
    }
}


void App::run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML_CALC");
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