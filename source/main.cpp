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

    Map map(sf::Vector2i(70, 70));

    std::vector<Pathfinder>pathfinders;

    sf::Clock clock;
    bool allDone;

    const int pathfinderAmount = 2;
    for(int i = 0; i < pathfinderAmount; i++) {
        pathfinders.emplace_back("test" + std::to_string(i), map);

        pathfinders.back().setStart (map.getTile(sf::Vector2i(rand() % 70, rand() % 70)));
        pathfinders.back().setTarget(map.getTile(sf::Vector2i(rand() % 70, rand() % 70)));
        pathfinders.back().setRange(2000);
    }

    sf::Event event = sf::Event();
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera.move(0, -5);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera.move(0, 5);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera.move(5, 0);

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera.move(-5, 0);


        map.update(window);

        for (auto &pathfinder : pathfinders)
            pathfinder.update(window);

        allDone = true;
        for (int i = 0; i < pathfinders.size(); i++) {
            /**if (pathfinders[i].getStatus() != Pathfinder::Working) {
                pathfinders.erase(pathfinders.begin() + i);
                i--;
            }**/

            if (pathfinders[i].getStatus() == Pathfinder::Working)
                allDone = false;
        }

        if (allDone && !pathfinders.empty()) {
            std::cout << "Time: " << clock.restart().asSeconds() << std::endl;

            /*for (auto &pathfinder : pathfinders)
                pathfinder.drawFoundPath();*/

            /** Testing getFoundPath() method **/
            for (auto &pathfinder : pathfinders) {
                std::vector<Tile*> path = pathfinder.getFoundPath();

                for (auto &tile : path) {
                    tile->setNodeState(pathfinder.getId(), Node::GoodPath);
                }
            }

            pathfinders.clear();
        }

        window.clear(sf::Color(0, 150, 255));

        window.setView(camera);
        window.draw(map);

        window.setView(window.getDefaultView());
        window.display();
    }

    return 0;
}