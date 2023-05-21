//
// Created by nektt on 5/21/2023.
//
#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f pos, const std::string &text) {
    _size = size;
    _pos = pos;
    _text.setString(sf::String(text));
    _bg.setSize(_size);
    _bg.setPosition(_pos);
    _text.setPosition(_pos);
}

void Button::setTextPosCenter() {
    auto txtBounds = _text.getLocalBounds();
    float x = _pos.x + (_size.x - txtBounds.width) / 2;
    float y = _pos.y + (_size.y - txtBounds.height) / 4;
    _text.setPosition(sf::Vector2f(x, y));
}


void Button::setFont(const sf::Font &font) {
    _text.setFont(font);
}

void Button::setColors(sf::Color bgColor, sf::Color selectedColor, sf::Color clickedColor, sf::Color textColor) {
    _bgColor = bgColor;
    _selectedColor = selectedColor;
    _clickedColor = clickedColor;
    _bg.setFillColor(_bgColor);
    _text.setFillColor(textColor);
}

void Button::setTextSizePx(int px) {
    _text.setCharacterSize(px);
}

bool Button::isPressed() {
    return _isPressed;
}

void Button::setText(const std::string &text) {
    _text.setString(sf::String(text));;
}

void Button::changeColorOnMousePosition(sf::Vector2i mousePos, bool isPressed) {
    if (mousePos.x >= _pos.x
        && mousePos.x <= (_pos.x + _size.x)
        && mousePos.y >= _pos.y
        && mousePos.y <= (_pos.y + _size.y)) {
        if (isPressed) {
            _bg.setFillColor(_clickedColor);
            _isPressed = true;
            return;
        } else
            _bg.setFillColor(_selectedColor);
    } else
        _bg.setFillColor(_bgColor);
    _isPressed = false;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_bg);
    target.draw(_text);
}