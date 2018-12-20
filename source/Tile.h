#ifndef ASTARALGORITHM_TILE_H
#define ASTARALGORITHM_TILE_H

#include <SFML/Graphics.hpp>
#include "Node.h"

class Tile : public sf::Drawable {
public:
    enum State {NotCollision, Collision};
    static const int WIDTH = 64, HEIGHT = 32;

    explicit Tile(sf::Texture& texture, State state, sf::Vector2f position);

    void handleEvent(sf::Event& event);
    void update(sf::RenderWindow& window);

    static sf::Vector2f toIsoPosition(sf::Vector2i position);
    static sf::Vector2i toTiledPosition(sf::Vector2f position);

    void setNodeState(Node::State newState);
    void setState(State newState);
    State& getState();
    Node* getNode();

    void setParent(Tile* newParent);
    Tile* getParent();

    sf::Vector2f getPosition();
    sf::Vector2i getTiledPosition();

private:
    Node node;
    sf::Sprite sprite;
    State state = State::NotCollision;
    Tile* parent = nullptr;

    void updateColor();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //ASTARALGORITHM_TILE_H
