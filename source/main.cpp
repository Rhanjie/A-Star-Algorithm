#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <math.h>

#include "Map.h"
#include "Pathfinder.h"

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1366, 768), "A* algorithm");
    sf::View camera;
    camera.setSize(sf::Vector2f(window.getSize()));

    Map map(sf::Vector2i(30, 30));
    Pathfinder pathfinder(map);

    pathfinder.setStart(map.getTile(sf::Vector2i(5, 5)));
    pathfinder.setTarget(map.getTile(sf::Vector2i(20, 25)));

    sf::Event event = sf::Event();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera.move(0, -1);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera.move(0, 1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera.move(1, 0);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera.move(-1, 0);


        map.update(window);
        pathfinder.update(window);

        window.clear(sf::Color(0, 150, 255));

        window.setView(camera);
        window.draw(map);

        window.setView(window.getDefaultView());
        //...

        window.display();
    }

    return 0;
}