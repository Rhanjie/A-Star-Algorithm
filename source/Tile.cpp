#include "Tile.h"

Tile::Tile(sf::Texture &texture, sf::Vector2f position)
    : node(position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Tile::handleEvent(sf::Event &event) {
    //...
}

void Tile::update(sf::RenderWindow &window) {
    //node.update();
}

Node &Tile::getNode() {
    return node;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Tile::setState(Tile::State newState) {
    state = newState;
}

Tile::State& Tile::getState() {
    return state;
}
