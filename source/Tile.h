#ifndef ASTARALGORITHM_TILE_H
#define ASTARALGORITHM_TILE_H

#include <SFML/Graphics.hpp>
#include "Node.h"

class Tile : public sf::Drawable {
public:
    enum State {NotCollision, Collision};

    Tile(sf::Texture& texture, sf::Vector2f position);

    void handleEvent(sf::Event& event);
    void update(sf::RenderWindow& window);

    void setState(State newState);
    State& getState();

    Node& getNode();

private:
    Node node;
    State state = State::NotCollision;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //ASTARALGORITHM_TILE_H
