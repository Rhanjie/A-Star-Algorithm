#ifndef ASTARALGORITHM_MAP_H
#define ASTARALGORITHM_MAP_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map : public sf::Drawable {
public:
    Map(sf::Vector2i mapSize);

    void resize(sf::Vector2i mapSize);
    void generate();

    sf::Vector2f getIsoPosition(sf::Vector2i position);
    sf::Vector2i getTiledPosition(sf::Vector2f position);

private:
    //TODO: Add resource manager
    std::map<std::string, sf::Texture*>textures;
    std::vector<std::vector<Tile*>>tiles;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //ASTARALGORITHM_MAP_H
