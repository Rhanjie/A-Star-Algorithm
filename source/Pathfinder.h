#ifndef ASTARALGORITHM_PATHFINDER_H
#define ASTARALGORITHM_PATHFINDER_H

#include "Tile.h"
#include "Map.h"

class Pathfinder {
public:
    explicit Pathfinder(Map& map);

    void update(sf::RenderWindow& window);

private:
    std::vector<Node*> openList;
    std::vector<Node*> closedList;

    Map* map = nullptr;
    Node* start = nullptr;
    Node* target = nullptr;



};

#endif //ASTARALGORITHM_PATHFINDER_H
