#include "Tile.h"

Tile::Tile(sf::Texture &texture, State state, sf::Vector2f position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);

    this->setState(state);
    this->updateColor("");
}

void Tile::addNewPathfind(const std::string &id) {
    if (nodes.find(id) == nodes.end()) {
        nodes.insert(std::make_pair(id, Node(this->getPosition())));

        this->setState(state);
        this->updateColor(id);
    }
}

void Tile::handleEvent(sf::Event &event) {
    //TODO: Implement
}

void Tile::update(sf::RenderWindow &window) {
    for (auto &node : nodes)
        node.second.update(window);
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

void Tile::setNodeState(const std::string &id, Node::State newState) {
    auto foundNode = nodes.find(id);

    if (foundNode != nodes.end()) {
        foundNode->second.setState(newState);

        this->updateColor(id);
    }
}

void Tile::setState(Tile::State newState) {
    state = newState;

    this->updateColor("");
}

Tile::State& Tile::getState() {
    return state;
}

Node* Tile::getNode(const std::string &id) {
    auto foundNode = nodes.find(id);

    if (foundNode != nodes.end())
        return &foundNode->second;

    else return nullptr;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Tile::updateColor(const std::string &id) {
    switch(state) {
        case State::NotCollision:
            sprite.setColor(sf::Color::Green);
            break;

        case State::Collision:
            sprite.setColor(sf::Color::Red);
            break;
    }

    sf::Color newColor = sprite.getColor();
    auto foundNode = nodes.find(id);
    if (!id.empty() && foundNode != nodes.end() && state == State::NotCollision && sprite.getColor() != sf::Color::Black) {
        switch (foundNode->second.getState()) {
            case Node::OpenList:
                //sprite.setColor(sf::Color::Cyan);
                //newColor.r += 20;
                newColor.r = 255;
                sprite.setColor(newColor);
                break;

            case Node::ClosedList:
                //sprite.setColor(sf::Color::Yellow);
                newColor.b = 255;
                //newColor.g += 20;
                sprite.setColor(newColor);
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
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

sf::Vector2i Tile::getTiledPosition() {
    return Tile::toTiledPosition(sprite.getPosition());
}

void Tile::setParent(const std::string &id, Tile *newParent) {
    parents[id] = newParent;

}

Tile* Tile::getParent(const std::string &id) {
    if (nodes.find(id) != nodes.end())
        return parents[id];

    else return nullptr;
}
