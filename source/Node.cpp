#include "Node.h"

Node::Node(sf::Vector2f position) {
    this->position = position;
}

void Node::handleEvent(sf::Event &event) {
    //TODO: Implement
}

void Node::update(sf::RenderWindow &window) {
    //TODO: Implement
}

void Node::setParentNodePosition(sf::Vector2i newPosition) {
    parentNodePosition = newPosition;
}

sf::Vector2i Node::getParentNodePosition() {
    return parentNodePosition;
}

void Node::setState(Node::State newState) {
    state = newState;
}

Node::State &Node::getState() {
    return state;
}

void Node::setMovementCost(int newCost) {
    movementCost = newCost;
}

int Node::getMovementCost() {
    return movementCost;
}

void Node::setHeuristicCost(int newCost) {
    heuristicCost = newCost;
}

int Node::getHeuristicCost() {
    return heuristicCost;
}

sf::Vector2f Node::getPosition() {
    return position;
}

void Node::resetCosts() {
    movementCost = 0;
}

void Node::resetState() {
    this->setState(State::Unknown);
}

void Node::resetParent() {
    parentNodePosition = sf::Vector2i(-1, -1);
}