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

sf::Vector2f Tile::toIsoPosition(sf::Vector2i position) {
    return sf::Vector2f(
            (float)(position.x - position.y) * Tile::WIDTH  / 2,
            (float)(position.x + position.y) * Tile::HEIGHT / 2
    );
}

sf::Vector2i Tile::toTiledPosition(sf::Vector2f position) {
    return sf::Vector2i(
            (int)((position.x / (Tile::WIDTH  / 2.0) + (position.y / (Tile::HEIGHT / 2.0)) + 1) / 2),
            (int)((position.y / (Tile::HEIGHT / 2.0) - (position.x / (Tile::WIDTH  / 2.0)) + 1) / 2)
    );
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

Node* Tile::getNode() {
    return &node;
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

        case Node::GoodPath:
            sprite.setColor(sf::Color::Black);
            break;

        case Node::Start:
            sprite.setColor(sf::Color::Blue);
            break;

        case Node::Target:
            sprite.setColor(sf::Color::Magenta);
            break;

        default:
            break;
    }
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

sf::Vector2i Tile::getTiledPosition() {
    return Tile::toTiledPosition(sprite.getPosition());
}

void Tile::setParent(Tile *newParent) {
    parent = newParent;

}

Tile* Tile::getParent() {
    return parent;
}
