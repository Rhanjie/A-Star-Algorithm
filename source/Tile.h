#ifndef ASTARALGORITHM_TILE_H
#define ASTARALGORITHM_TILE_H

#include <SFML/Graphics.hpp>
#include "Node.h"

class Tile : public sf::Drawable {
public:
    enum State {NotCollision, Collision};

    explicit Tile(sf::Texture& texture, sf::Vector2f position);

    void handleEvent(sf::Event& event);
    void update(sf::RenderWindow& window);

    void setState(State newState);
    State& getState();

    Node& getNode();

private:
    Node node;
    sf::Sprite sprite;
    State state = State::NotCollision;

    void updateColor();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //ASTARALGORITHM_TILE_H
