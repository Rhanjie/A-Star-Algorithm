#include "Tile.h"

Tile::Tile(sf::Texture &texture, State state, sf::Vector2f position)
    : node(position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);

    this->setState(state);
    this->updateColor();
}

void Tile::handleEvent(sf::Event &event) {
    //TODO: Implement
}

void Tile::update(sf::RenderWindow &window) {
    node.update(window);
}

void Tile::setNodeState(Node::State newState) {
    node.setState(newState);

    this->updateColor();
}

void Tile::setState(Tile::State newState) {
    state = newState;

    this->updateColor();
}

Tile::State& Tile::getState() {
    return state;
}

Node &Tile::getNode() {
    return node;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Tile::updateColor() {
    switch(state) {
        case State::NotCollision:
            sprite.setColor(sf::Color::Green);
            break;

        case State::Collision:
            sprite.setColor(sf::Color::Red);
            break;
    }

    switch(node.getState()) {
        case Node::OpenList:
            sprite.setColor(sf::Color::Cyan);
            break;

        case Node::ClosedList:
            sprite.setColor(sf::Color::Yellow);
            break;

        case Node::Start:
            sprite.setColor(sf::Color::Blue);
            break;

        case Node::Target:
            sprite.setColor(sf::Color::Black);
            break;

        default:
            break;
    }

    //TODO: Implement
}