#include "Map.hh"

Map* Map::instance = new Map();

Map& Map::GetInstance() {
    return *instance;
}

Map::Map() {}

Map::~Map() {}

void Map::load(sf::Vector2u tileSize, unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    this->loadCalque(baseCalque, basetiles, "houvet_b/resources/datas/pokemon-base_Base.csv", tileSize);
    this->loadCalque(collisionCalque, collisiontiles, "houvet_b/resources/datas/pokemon-base_Collision.csv", tileSize);
}

void Map::loadCalque(sf::VertexArray &calque, std::vector<int> &tiles, std::string filename, sf::Vector2u tileSize) {
    // on charge la texture du tileset
    sf::Texture tileset = ResourceManager::GetInstance().getMainTileset();

    //Lecture du fichier csv
    std::ifstream file ( filename );
    std::string value;
    while ( file.good() )
    {
        getline ( file, value, ',' );
        tiles.push_back(std::stoi(value));
    }

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    calque.setPrimitiveType(sf::Quads);
    calque.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * width];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &calque[(i + j * width) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // on applique la texture du tileset
    states.transform *= getTransform();
    states.texture = &ResourceManager::GetInstance().getMainTileset();

    //on dessine les tableau de vertex
    target.draw(baseCalque, states);
    target.draw(collisionCalque, states);
}

//Retourne 1 si la case demandée est une case sur laquelle on peut marcher
int Map::isValidTile(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        LogManager::error_logs("La case demandée est invalide");
        return (-1);
    }
    else if (collisiontiles[x + y * width ] == -1)
        return (1);
    else
        return (0);
}

//Retourne 1 si la case demandée est une case sur laquelle on peut rencontrer un monstre
int Map::isFightTile(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        LogManager::error_logs("La case demandée est invalide");
        return (-1);
    }
    else if (basetiles[x + y * width ] == 5)
        return (1);
    else
        return (0);
}

void Map::free() {
    delete instance;
}


