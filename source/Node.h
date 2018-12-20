#ifndef ASTARALGORITHM_NODE_H
#define ASTARALGORITHM_NODE_H

#include <SFML/Graphics.hpp>

class Node {
public:
    enum State {Unknown, Start, Target, OpenList, ClosedList, GoodPath};

    explicit Node(sf::Vector2f position);

    void handleEvent(sf::Event& event);
    void update(sf::RenderWindow& window);

    void setParent(Node* newParent);
    Node* getParent();

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
    Node* parent = nullptr;
    State state = State::Unknown;

    int movementCost = 0;
    int heuristicCost = 0;

};

#endif //ASTARALGORITHM_NODE_H
