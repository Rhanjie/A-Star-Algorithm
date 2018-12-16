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
            sf::Vector2f position = this->getIsoPosition(sf::Vector2i(x, y));

            //TODO: Improve map generator
            if (rand()%100 < 80)
                tiles[y][x] = new Tile(*textures["grass"], Tile::NotCollision, position);

            else tiles[y][x] = new Tile(*textures["wall"], Tile::Collision, sf::Vector2f(position.x, position.y - 20));
        }
    }
}

sf::Vector2f Map::getIsoPosition(sf::Vector2i position) {
    return sf::Vector2f(
            (float)(position.x - position.y) * Tile::WIDTH  / 2,
            (float)(position.x + position.y) * Tile::HEIGHT / 2
    );
}

sf::Vector2i Map::getTiledPosition(sf::Vector2f position) {
    return sf::Vector2i(
            (int)((position.x / (Tile::WIDTH  / 2.0) + (position.y / (Tile::HEIGHT / 2.0)) + 1) / 2),
            (int)((position.y / (Tile::HEIGHT / 2.0) - (position.x / (Tile::WIDTH  / 2.0)) + 1) / 2)
    );
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto &row : tiles) {
        for(auto &tile : row) {
            target.draw(*tile);
        }
    }
}