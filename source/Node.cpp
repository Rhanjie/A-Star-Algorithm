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

void Node::setParent(Node* newParent) {
    parent = newParent;
}

Node* Node::getParent() {
    return parent;
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
    parent = nullptr;
}