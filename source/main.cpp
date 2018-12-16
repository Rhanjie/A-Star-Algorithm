#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <math.h>

#include "Tile.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "A* algorithm");

    //Map map;
    //PathFinder pathfinder(map);

    sf::Texture texture;
    texture.loadFromFile("../assets/grass.png");

    Tile tile(texture, sf::Vector2f(100, 100));

    sf::Event event = sf::Event();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //map.update(window);
        //pathfinder.update(window);


        window.clear();

        //map.draw(window);

        window.draw(tile);

        window.display();
    }

    return 0;
}