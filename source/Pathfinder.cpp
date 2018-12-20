#include "Pathfinder.h"

Pathfinder::Pathfinder(Map &map) {
    this->map = &map;
}

void Pathfinder::update(sf::RenderWindow &window) {
    sf::Vector2i mapSize = map->getMapSize();


    if (clock.getElapsedTime() >= sf::seconds(0.1)) {
        this->step();

        clock.restart();
    }

}

void Pathfinder::setStart(Tile& newStart) {
    start = &newStart;
    start->setNodeState(Node::Start);
}

void Pathfinder::setTarget(Tile& newTarget) {
    target = &newTarget;
    target->setNodeState(Node::Target);
}

void Pathfinder::setRange(unsigned int range) {
    maxCost = range;
}

void Pathfinder::clearStart() {
    start = nullptr;
}

void Pathfinder::clearTarget() {
    target = nullptr;
}

void Pathfinder::step() {
    if (start == nullptr || target == nullptr || status != Pathfinder::Working)
        return;

    if (openList.empty() && closedList.empty()) {
        openList.emplace_back(start);
        return;
    }

    if (!closedList.empty()) {
        if (openList.empty() || countTotalCost(closedList.back()) >= maxCost) {
            std::cout << "Nieznaleziono sciezki!\n";

            status = Pathfinder::NoPath;
            return;
        }

        if (!closedList.empty() && closedList.back() == target) {
            //FOUND TARGET

            start->setNodeState(Node::Start);
            target->setNodeState(Node::Target);

            this->clearStart();
            this->clearTarget();

            //DrawPath
            Tile* tile = closedList.back();
            Node* neighbor = tile->getNode()->getParent();

            while(tile->getNode()->getParent() != nullptr) {

                if (tile->getNode()->getState() != Node::Start &&
                    tile->getNode()->getState() != Node::Target)
                    tile->setNodeState(Node::GoodPath);

                tile = tile->getParent();
            }

            //...
            status = Pathfinder::FoundPath;
            return;
        }
    }


    int index = this->findLowestScoreIndex();
    if (index != -1) {
        this->exploreNeighbors(index);

        //...
    }
}

void Pathfinder::exploreNeighbors(int index) {
    Tile* tile = *(openList.begin() + index);
    openList.erase(openList.begin() + index);
    closedList.emplace_back(tile);
    tile->setNodeState(Node::ClosedList);

    sf::Vector2i position = tile->getTiledPosition();
    std::vector<sf::Vector2i> neighborPositions {
            sf::Vector2i(position.x + 1, position.y),
            sf::Vector2i(position.x - 1, position.y),
            sf::Vector2i(position.x, position.y + 1),
            sf::Vector2i(position.x, position.y - 1),
    };


    for (auto &neighborPosition : neighborPositions) {
        if (neighborPosition.x >= 0 && neighborPosition.x < map->getMapSize().x &&
            neighborPosition.y >= 0 && neighborPosition.y < map->getMapSize().y) {
            Tile *neighbor = &map->getTile(neighborPosition);

            if (neighbor->getState() != Tile::Collision) {
                if (std::find(closedList.begin(), closedList.end(), neighbor) == closedList.end()) {
                    if (std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                        openList.push_back(neighbor);
                        openList.back()->setNodeState(Node::OpenList);

                        openList.back()->getNode()->setMovementCost(cost);
                        openList.back()->getNode()->setHeuristicCost(this->countHeuristic(openList.back()));
                        openList.back()->getNode()->setParent(closedList.back()->getNode());
                        openList.back()->setParent(closedList.back());
                    }
                }
            }
        }
    }
}

int Pathfinder::countTotalCost(Tile* tile) {
    sf::Vector2i difference = target->getTiledPosition() - tile->getTiledPosition();
    difference.x = abs(difference.x) * 10;
    difference.y = abs(difference.y) * 10;

    int heuristic = difference.x + difference.y;
    if (tile->getNode()->getParent() != nullptr)
        tile->getNode()->setMovementCost(tile->getNode()->getParent()->getMovementCost() + cost);
    else tile->getNode()->setMovementCost(cost);

    tile->getNode()->setHeuristicCost(heuristic);

    std::cout << difference.x << " (::) " << difference.y << std::endl;
    std::cout << "Total cost: " << heuristic + tile->getNode()->getMovementCost() << std::endl;
    return heuristic + tile->getNode()->getMovementCost();
}

int Pathfinder::findLowestScoreIndex() {
    int lowestF = 999999;
    int index = -1;

    for (int i = 0; i < openList.size(); i++) {
        int countedTotalCost = this->countTotalCost(openList[i]);

        if (lowestF > countedTotalCost) {
            lowestF = countedTotalCost;

            index = i;
        }
    }

    return index;
}

Pathfinder::Status Pathfinder::getStatus() {
    return status;
}

int Pathfinder::countHeuristic(Tile *tile) {
    sf::Vector2i difference = target->getTiledPosition() - tile->getTiledPosition();
    difference.x = abs(difference.x) * 10;
    difference.y = abs(difference.y) * 10;

    return difference.x + difference.y;
}
