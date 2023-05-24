
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Cfg.h"
#include "UI.h"



int main() {
    sf::RenderWindow window(sf::VideoMode(Cfg::WindowSize.x, Cfg::WindowSize.y), "SFML works!", sf::Style::None);

    Field field;
    UserInterface UI(&window, field);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            UI.detectCollisions(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
            field.detectCollisions(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
            field.getNumber();
        }

        window.clear(sf::Color(140, 245, 201));
        window.draw(field);
        window.draw(UI);
        window.display();
    }
    return 0;
}
