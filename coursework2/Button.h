//
// Created by nektt on 5/21/2023.
//

#ifndef COURSEWORK2_BUTTON_H
#define COURSEWORK2_BUTTON_H

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
    sf::Vector2f _size;
    sf::Vector2f _pos;
    sf::RectangleShape _bg;
    sf::Text _text;
    sf::Color _bgColor;
    sf::Color _selectedColor;
    sf::Color _clickedColor;

    bool _isPressed = false;
public:
    Button(){}
    Button(sf::Vector2f size, sf::Vector2f pos, const std::string &text);


    void setTextPosCenter();

    void setFont(const sf::Font &font);

    void setColors(sf::Color bgColor, sf::Color selectedColor, sf::Color clickedColor, sf::Color textColor);

    void setTextSizePx(int px);

    bool isPressed();

    void setText(const std::string &text);

    void changeColorOnMousePosition(sf::Vector2i mousePos, bool isPressed);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif //COURSEWORK2_BUTTON_H
