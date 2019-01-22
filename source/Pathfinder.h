#ifndef ASTARALGORITHM_PATHFINDER_H
#define ASTARALGORITHM_PATHFINDER_H

#include "Tile.h"
#include "Map.h"
#include <cmath>
#include <iostream>
#include <limits.h>


class Pathfinder {
public:
    enum Status {Working, FoundPath, NoPath};

    explicit Pathfinder(const std::string &id, Map& map);

    void setStart(Tile &newStart);
    void setTarget(Tile &newTarget);
    void setRange(unsigned int range);
    void update(sf::RenderWindow& window);

    void drawFoundPath();

    void clearStart();
    void clearTarget();

    Status getStatus();

private:
    std::vector<Tile*> openList;
    std::vector<Tile*> closedList;
    //std::priority_queue<Tile*> openList;
    //std::priority_queue<Tile*> closedList;

    Status status = Status::Working;

    Map* map     = nullptr;
    Tile* start  = nullptr;
    Tile* target = nullptr;
    sf::Clock clock;

    int cost = 10;
    int maxCost = 10000;
    std::string id = "";

    void step();
    void exploreNeighbors(int index);

    int countHeuristic(Tile* tile);
    int countTotalCost(Tile* tile);
    int findLowestScoreIndex();
};

#endif //ASTARALGORITHM_PATHFINDER_H
