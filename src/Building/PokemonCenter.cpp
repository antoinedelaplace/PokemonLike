//
// Created by Benoît - Xavier HOUVET on 28/04/2017.
//

#include "PokemonCenter.hh"


void PokemonCenter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    PlayerEntity &pm = PlayerEntity::getInstance();
    this->drawBlackColorBackground(target, states);
    this->drawBackground(target, states);
    target.draw(pm);
}



int PokemonCenter::isValidTile(int x, int y) {
    if (x < 0 || x >= 33 || y < 0 || y >= 53) {
        LogManager::error_logs("La case demandée est invalide");
        return (-1);
    }
    else
        return (collisiontiles[x + (y * 33)]);
}

void PokemonCenter::drawBackground(sf::RenderTarget &target, sf::RenderStates states) const {
    Game &game = Game::GetInstance();
    states.texture = &ResourceManager::GetInstance().getBuildingTileset();

    //Dessin du background
    int differencex = 52;
    int differencey = 272;
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(differencex, differencey+0);
    background[1].position = sf::Vector2f(differencex+448, differencey+0);
    background[2].position = sf::Vector2f(differencex+448, differencey+292);
    background[3].position = sf::Vector2f(differencex+0, differencey+292);

    background[0].texCoords = sf::Vector2f(690, 190);
    background[1].texCoords = sf::Vector2f(914, 190);
    background[2].texCoords = sf::Vector2f(914, 332);
    background[3].texCoords = sf::Vector2f(690, 332);

    target.draw(background, states);
}

void PokemonCenter::drawBlackColorBackground(sf::RenderTarget &target, sf::RenderStates states) const {
    Game &game = Game::GetInstance();
    states.texture = &ResourceManager::GetInstance().getBuildingTileset();

    //Dessin du background

    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(game.getWindowWidth(), 0);
    background[2].position = sf::Vector2f(game.getWindowWidth(), game.getWindowHeight());
    background[3].position = sf::Vector2f(0, game.getWindowHeight());

    background[0].texCoords = sf::Vector2f(1, 1);
    background[1].texCoords = sf::Vector2f(2, 1);
    background[2].texCoords = sf::Vector2f(2, 2);
    background[3].texCoords = sf::Vector2f(1, 2);

    target.draw(background, states);

}

void PokemonCenter::Notify(char i) {
    std::cout << i << std::endl;
    PlayerEntity &pm = PlayerEntity::getInstance();
    Game &game = Game::GetInstance();
    int isvalid;
    //std::cout << (game.getState() == BUILDING) << std::endl;
    if (game.getState() == BUILDING) {
        if (i != 'P') {
            if (!pm.turn(i)) {
                switch (i) {
                    case ('Z'):
                        std::cout << ((this->isValidTile((pm.getX() / 16) - 1, ((pm.getY() - 16) / 16) - 1))) << std::endl;
                        if ((this->isValidTile((pm.getX() / 16) - 1, ((pm.getY() - 16) / 16) - 1)) == 1)
                            pm.setIsMoving();
                        if ((this->isValidTile((pm.getX() / 16) - 1, ((pm.getY() - 16) / 16) - 1)) == 2) {
                            std::cout << "debug" << std::endl;
                            pm.healAllTeam();
                        }
                        break;
                    case ('S'):
                        //isvalid = this->isValidTile((pm.getX() / 16) - 1, ((pm.getY() + 16) / 16) - 1);
                        if ((this->isValidTile((pm.getX() / 16) - 1, ((pm.getY() + 16) / 16) - 1)) == 1) {
                            pm.setIsMoving();
                        }
                        if ((this->isValidTile((pm.getX() / 16) - 1, ((pm.getY() + 16) / 16) - 1)) == 3) {
                            game.setState(WORLD);
                            pm.setX(X);
                            pm.setY(Y);
                        }
                        break;
                    case ('Q'):
                        //isvalid = this->isValidTile(((pm.getX() - 16) / 16) - 1, (pm.getY() / 16) - 1);
                        if ((this->isValidTile(((pm.getX() - 16) / 16) - 1, (pm.getY() / 16) - 1)) == 1) {
                            pm.setIsMoving();
                        }
                        break;
                    case ('D'):
                        //isvalid = this->isValidTile(((pm.getX() + 16) / 16) - 1, (pm.getY() / 16) - 1);
                        if ((this->isValidTile(((pm.getX() + 16) / 16) - 1, (pm.getY() / 16) - 1)) == 1) {
                            pm.setIsMoving();
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

PokemonCenter::PokemonCenter() {
    PlayerEntity &pm = PlayerEntity::getInstance();
    int x = pm.getX();
    int y = pm.getY();
    pm.setX(this->X);
    pm.setY(this->Y);
    this->X = x;
    this->Y = y;
    std::ifstream file ( "houvet_b/resources/datas/ColisionPokemonCenter.csv" );
    std::string value;
    while ( file.good() )
    {
        getline ( file, value, ',' );
        this->collisiontiles.push_back(std::stoi(value));
    }
}
