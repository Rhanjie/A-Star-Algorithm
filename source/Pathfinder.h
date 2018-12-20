#ifndef ASTARALGORITHM_PATHFINDER_H
#define ASTARALGORITHM_PATHFINDER_H

#include "Tile.h"
#include "Map.h"
#include <cmath>
#include <iostream>
#include <limits.h>


class Pathfinder {
public:
    explicit Pathfinder(Map& map);

    void setStart(Tile &newStart);
    void setTarget(Tile &newTarget);
    void update(sf::RenderWindow& window);

    void clearStart();
    void clearTarget();

    bool pathFound();

private:
    std::vector<Tile*> openList;
    std::vector<Tile*> closedList;

    Map* map     = nullptr;
    Tile* start  = nullptr;
    Tile* target = nullptr;

    int cost = 10;
    bool isFound = false;

    void step();
    void exploreNeighbors(int index);

    int countCost(Tile* tile);
    int countHeuristic(Tile* tile);

    int countTotalCost(Tile* tile);

    int findLowestScoreIndex();


};

#endif //ASTARALGORITHM_PATHFINDER_H
