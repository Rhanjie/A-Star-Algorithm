#include "Pathfinder.h"

Pathfinder::Pathfinder(const std::string &id, Map &map) {
    this->id = id;
    this->map = &map;
}

void Pathfinder::update(sf::RenderWindow &window) {
    sf::Vector2i mapSize = map->getMapSize();


    //if (clock.getElapsedTime() >= sf::microseconds(5)) {
        this->step();

        clock.restart();
    //}

}

void Pathfinder::setStart(Tile& newStart) {
    start = &newStart;

    start->addNewPathfind(id);
    start->setNodeState(id, Node::Start);
}

void Pathfinder::setTarget(Tile& newTarget) {
    target = &newTarget;

    target->addNewPathfind(id);
    target->setNodeState(id, Node::Target);
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
            status = Pathfinder::NoPath;
            return;
        }

        if (!closedList.empty() && closedList.back() == target) {
            std::cout << "Another algorithm has finished work!\n";
            status = Pathfinder::FoundPath;

            this->drawFoundPath();
            return;
        }
    }


    int index = this->findLowestScoreIndex();
    if (index != -1) {
        this->exploreNeighbors(index);

        //...
    }

    else status = Pathfinder::NoPath;
}

void Pathfinder::exploreNeighbors(int index) {
    Tile* tile = *(openList.begin() + index);
    openList.erase(openList.begin() + index);
    closedList.emplace_back(tile);
    tile->addNewPathfind(id);
    tile->setNodeState(id, Node::ClosedList);

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

            if (neighbor->getState() != Tile::Collision || neighbor == start || neighbor == target) {
                if (std::find(closedList.begin(), closedList.end(), neighbor) == closedList.end()) {
                    if (std::find(openList.begin(), openList.end(), neighbor) == openList.end()) {
                        openList.push_back(neighbor);
                        neighbor->addNewPathfind(id);
                        openList.back()->setNodeState(id, Node::OpenList);

                        openList.back()->getNode(id)->setMovementCost(cost);
                        openList.back()->getNode(id)->setHeuristicCost(this->countHeuristic(openList.back()));
                        openList.back()->getNode(id)->setParent(closedList.back()->getNode(id));
                        openList.back()->setParent(id, closedList.back());
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
    if (tile->getNode(id)->getParent() != nullptr)
        tile->getNode(id)->setMovementCost(tile->getNode(id)->getParent()->getMovementCost() + cost);
    else tile->getNode(id)->setMovementCost(cost);

    tile->getNode(id)->setHeuristicCost(heuristic);

    //std::cout << difference.x << " (::) " << difference.y << std::endl;
    //std::cout << "Total cost: " << heuristic + tile->getNode(id)->getMovementCost() << std::endl;
    return heuristic + tile->getNode(id)->getMovementCost();
}

int Pathfinder::findLowestScoreIndex() {
    int lowestF = maxCost;
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

void Pathfinder::drawFoundPath() {
    if (status == Pathfinder::FoundPath) {
        if (start != nullptr && target != nullptr) {
            start->setNodeState(id, Node::Start);
            target->setNodeState(id, Node::Target);

            //this->clearStart();
            //this->clearTarget();
        }

        Tile *tile = closedList.back();
        Node *neighbor = tile->getNode(id)->getParent();

        while (tile->getNode(id)->getParent() != nullptr) {

            if (tile->getNode(id)->getState() != Node::Start &&
                tile->getNode(id)->getState() != Node::Target)
                tile->setNodeState(id, Node::GoodPath);

            tile = tile->getParent(id);
        }
    }
}
