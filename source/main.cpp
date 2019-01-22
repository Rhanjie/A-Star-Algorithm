#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <math.h>
#include "cstdlib"

#include "Map.h"
#include "Pathfinder.h"

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1366, 768), "RhA* Algorithm");

    sf::View camera;
    camera.setSize(sf::Vector2f(window.getSize()));
    camera.zoom(2);

    Map map(sf::Vector2i(50, 50));

    std::vector<Pathfinder>pathfinders;

    const int pathfinderAmounts = 3;
    for(int i = 0; i < pathfinderAmounts; i++) {
        pathfinders.emplace_back("test" + std::to_string(i), map);

        pathfinders.back().setStart (map.getTile(sf::Vector2i(rand() % 40, rand() % 40)));
        pathfinders.back().setTarget(map.getTile(sf::Vector2i(rand() % 40, rand() % 40)));
        pathfinders.back().setRange(1000);
    }

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

        for (int i = 0; i < pathfinders.size(); i++)
            pathfinders[i].update(window);

        bool allDone = true;
        for (int i = 0; i < pathfinders.size(); i++) {
            if (pathfinders[i].getStatus() != Pathfinder::Working) {
                //pathfinders.erase(pathfinders.begin() + i);
                //i--;

                allDone = false;
            }
        }

        if (allDone) {
            for (int i = 0; i < pathfinderAmounts; i++) {
                pathfinders[i].drawFoundPath();
            }
        }

        window.clear(sf::Color(0, 150, 255));

        window.setView(camera);
        window.draw(map);

        window.setView(window.getDefaultView());
        window.display();
    }

    return 0;
}