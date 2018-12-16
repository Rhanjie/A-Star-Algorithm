#ifndef ASTARALGORITHM_NODE_H
#define ASTARALGORITHM_NODE_H

#include <SFML/Graphics.hpp>

//TODO: Maybe put code below in the Tile class
class Node {
public:
    enum State {Unknown, Start, Target, OpenList, ClosedList};

    explicit Node(sf::Vector2f position);

    void handleEvent(sf::Event& event);
    void update(sf::RenderWindow& window);

    void setParentNodePosition(sf::Vector2i newPosition);
    sf::Vector2i getParentNodePosition();

    void setState(State newState);
    State& getState();

    void setMovementCost(int newCost);
    int getMovementCost();

    void setHeuristicCost(int newCost);
    int getHeuristicCost();

    sf::Vector2f getPosition();

    void resetCosts();
    void resetState();
    void resetParent();


private:
    sf::Vector2f position = sf::Vector2f(0, 0);
    sf::Vector2i parentNodePosition = sf::Vector2i(-1, -1);
    State state = State::Unknown;

    int movementCost = 0;
    int heuristicCost = 0;

};

#endif //ASTARALGORITHM_NODE_H
