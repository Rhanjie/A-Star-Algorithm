#include "Map.h"

Map::Map(sf::Vector2i mapSize) {
    auto *texture = new sf::Texture();
    texture->loadFromFile("../assets/grass.png");
    textures["grass"] = texture;

    texture = new sf::Texture();
    texture->loadFromFile("../assets/wall.png");
    textures["wall"] = texture;

    this->resize(mapSize);
    this->generate();
}

void Map::resize(sf::Vector2i mapSize) {
    tiles.resize(mapSize.y);
    for(auto y = 0; y < tiles.size(); y++) {
        tiles[y].resize(mapSize.x);

        for (auto x = 0; x < tiles[y].size(); x++) {
            tiles[y][x] = nullptr;
        }
    }
}

void Map::generate() {
    for(auto y = 0; y < tiles.size(); y++) {
        for (auto x = 0; x < tiles[y].size(); x++) {
            sf::Vector2f position = Tile::toIsoPosition(sf::Vector2i(x, y));

            //TODO: Improve map generator
            if (rand()%100 < 70)
                tiles[y][x] = new Tile(*textures["grass"], Tile::NotCollision, position);

            else tiles[y][x] = new Tile(*textures["wall"], Tile::Collision, sf::Vector2f(position.x, position.y - 20));
        }
    }
}

void Map::update(sf::RenderWindow &window) {
    for(auto &row : tiles) {
        for(auto &tile : row) {
            tile->update(window);
        }
    }
}

sf::Vector2i Map::getMapSize() {
    return sf::Vector2i((int)tiles[0].size(), (int)tiles.size());
}

Tile &Map::getTile(sf::Vector2i position) {
    return *tiles[position.y][position.x];
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto &row : tiles) {
        for(auto &tile : row) {
            target.draw(*tile);
        }
    }
}