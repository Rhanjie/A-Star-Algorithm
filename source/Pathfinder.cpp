#include "Pathfinder.h"

Pathfinder::Pathfinder(Map &map) {
    this->map = &map;


}

void Pathfinder::update(sf::RenderWindow &window) {
    sf::Vector2i mapSize = map->getMapSize();

    for (int y = 0; y < mapSize.y; y++) {
        for (int x = 0; x < mapSize.x; x++) {
            Tile* tile = &map->getTile(sf::Vector2i(x, y));



            //TODO: Debug code
            if (tile->getNode().getState() == Node::Unknown && tile->getState() == Tile::Collision) {
                tile->setNodeState(Node::OpenList);
            }
        }
    }
};
