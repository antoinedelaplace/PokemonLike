#include "Fight.hh"

Fight::Fight() : IObserver() {
    Game &game = Game::GetInstance();
    //Rencontre d'un pokemon sauvage aléatoire
    front = ListPokemon::GetInstance().GetPokemonRandom();
    //Premier pokemon de la liste du joueur
    back = PlayerEntity::getInstance().getFirstPokemonAlive();

    std::cout << "lvl pokemon en face : " << front->getLevel() << std::endl;
    std::cout << "lvl de son pokemon : " << back->getLevel() << std::endl;

    xpGive = 0;
    if (front == NULL || back == NULL) {
        LogManager::error_logs("erreur de récupération des pokemons");
    }
    //Par defaut le menu est sur le menu des actions
    menu = -1;
    //Par defaut le selector est sur l'entrée attaque
    selector = 0;
    firstSelector = 0;
    //Positionne le state sur begin
    state = BEGIN;
    //on Séléctionne le nb max d'objets par combat
    nbMaxObject = 5;
    nbObjectUsed = 0;
}

Fight::~Fight() {}

Pokemon* Fight::getFront(){
    return front;
}

Pokemon* Fight::getBack(){
    return back;
}

void Fight::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    this->drawBackground(target, states);
    switch (state) {
        case BEGIN:
            this->drawFrontPokemon(target, states);
            this->drawPlayer(target, states);
            this->drawDescriptionMenu(target, states);
            this->writeTextBegin(target, states);
            break;
        case CHOOSE_ACTION:
        case DELETE_POKEMON:
            this->drawChoiceMenu(target, states);
            this->writeTextMenu(target, states);
            this->drawFrontPokemon(target, states);
            if (this->back->getHp() > 0) {
                this->drawBackPokemon(target, states);
                this->setXPBar(target,states);
            }
            this->setHPBar(target, states);
            break;
        case FIRST_ACTION:
            this->drawDescriptionMenu(target, states);
            this->drawFrontPokemon(target, states);
            if (this->back->getHp() > 0) {
                this->drawBackPokemon(target, states);
                this->setXPBar(target,states);
            }
            this->setHPBar(target, states);
            this->writeTextAction(target, states);
            break;
        case SECOND_ACTION:
            this->drawDescriptionMenu(target, states);
            this->drawFrontPokemon(target, states);
            this->drawBackPokemon(target, states);
            this->setHPBar(target, states);
            this->setXPBar(target,states);
            this->writeTextAction(target, states);
            break;
        case DEAD:
            this->drawDescriptionMenu(target, states);
            if (this->front->getHp() > 0)
                this->drawFrontPokemon(target, states);
            else {
                this->drawBackPokemon(target, states);
                this->setXPBar(target,states);
            }
            this->setHPBar(target, states);
            this->writeTextDead(target, states);
            break;
        case CATCH_FAIL:
            this->drawDescriptionMenu(target, states);
            this->drawFrontPokemon(target, states);
            this->drawBackPokemon(target, states);
            this->setXPBar(target,states);
            this->setHPBar(target, states);
            this->writeTextCatchFail(target, states);
            break;
        case CATCH_OK:
            this->drawDescriptionMenu(target, states);
            this->drawFrontPokemon(target, states);
            this->drawBackPokemon(target, states);
            this->setXPBar(target,states);
            this->setHPBar(target, states);
            this->writeTextCatchOk(target, states);
            break;
        case TEAM_FULL:
            this->drawDescriptionMenu(target, states);
            this->drawFrontPokemon(target, states);
            this->drawBackPokemon(target, states);
            this->setXPBar(target,states);
            this->setHPBar(target, states);
            this->writeTextTeamFull(target, states);
            break;
        case GIVE_XP:
            this->drawDescriptionMenu(target, states);
            this->drawBackPokemon(target, states);
            this->setHPBar(target, states);
            this->setXPBar(target,states);
            this->writeTextGiveXP(target, states);
            break;
        case END:
            this->drawFrontPokemon(target, states);
            this->setHPBar(target, states);
            this->drawPlayer(target, states);
            this->drawDescriptionMenu(target, states);
            this->writeTextEnd(target, states);
            break;
        case LEVEL_UP:
            this->drawDescriptionMenu(target, states);
            this->drawBackPokemon(target, states);
            this->setHPBar(target, states);
            this->setXPBar(target,states);
            this->writeTextLevelUp(target, states);
            break;
    }
}

void Fight::drawBackground(sf::RenderTarget &target, sf::RenderStates states) const {
    Game &game = Game::GetInstance();
    states.texture = &ResourceManager::GetInstance().getBackgroundsTileset();

    //Dessin du background
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(game.getWindowWidth(), 0);
    background[2].position = sf::Vector2f(game.getWindowWidth(), game.getWindowHeight() - 200);
    background[3].position = sf::Vector2f(0, game.getWindowHeight() - 200);

    background[0].texCoords = sf::Vector2f(1, 21);
    background[1].texCoords = sf::Vector2f(243, 21);
    background[2].texCoords = sf::Vector2f(243, 135);
    background[3].texCoords = sf::Vector2f(1, 135);

    target.draw(background, states);
}

void Fight::drawChoiceMenu(sf::RenderTarget &target, sf::RenderStates states) const {
    Game &game = Game::GetInstance();
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();

    //Affichage du menu de choix des actions
    sf::VertexArray choiceMenu(sf::Quads, 4);
    choiceMenu[0].position = sf::Vector2f(0, game.getWindowHeight() - 206);
    choiceMenu[1].position = sf::Vector2f(game.getWindowWidth(), game.getWindowHeight() - 206);
    choiceMenu[2].position = sf::Vector2f(game.getWindowWidth(), game.getWindowHeight());
    choiceMenu[3].position = sf::Vector2f(0, game.getWindowHeight());

    choiceMenu[0].texCoords = sf::Vector2f(297, 4);
    choiceMenu[1].texCoords = sf::Vector2f(457, 4);
    choiceMenu[2].texCoords = sf::Vector2f(457, 52);
    choiceMenu[3].texCoords = sf::Vector2f(297, 52);

    target.draw(choiceMenu, states);

    //Dessin du selecteur (par défaut sur attaque)
    sf::VertexArray selector(sf::Quads, 4);

    selector[0].texCoords = sf::Vector2f(269, 4);
    selector[1].texCoords = sf::Vector2f(274, 4);
    selector[2].texCoords = sf::Vector2f(274, 13);
    selector[3].texCoords = sf::Vector2f(269, 13);

    int xselector = 50;
    int ySelector = game.getWindowHeight() - 138;

    if (this->selector % 2 ==  1)
        xselector += 230;
    if (this->selector == this->firstSelector + 2 || this->selector == this->firstSelector + 3)
        ySelector += 70;

    selector[0].position = sf::Vector2f(xselector, ySelector);
    selector[1].position = sf::Vector2f(xselector + 10, ySelector);
    selector[2].position = sf::Vector2f(xselector + 10, ySelector + 18);
    selector[3].position = sf::Vector2f(xselector, ySelector + 18);

    target.draw(selector, states);
}

void Fight::drawDescriptionMenu(sf::RenderTarget &target, sf::RenderStates states) const {
    Game &game = Game::GetInstance();
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();

    //Affichage du menu de description
    sf::VertexArray beginMenu(sf::Quads, 4);
    beginMenu[0].position = sf::Vector2f(0, game.getWindowHeight() - 206);
    beginMenu[1].position = sf::Vector2f(game.getWindowWidth(), game.getWindowHeight() - 206);
    beginMenu[2].position = sf::Vector2f(game.getWindowWidth(), game.getWindowHeight());
    beginMenu[3].position = sf::Vector2f(0, game.getWindowHeight());

    beginMenu[0].texCoords = sf::Vector2f(297, 56);
    beginMenu[1].texCoords = sf::Vector2f(537, 56);
    beginMenu[2].texCoords = sf::Vector2f(537, 104);
    beginMenu[3].texCoords = sf::Vector2f(297, 104);

    target.draw(beginMenu, states);

    this->drawRedArrow(target, states, 0);
}

void Fight::drawRedArrow(sf::RenderTarget &target, sf::RenderStates states, int back) const {
    Game &game = Game::GetInstance();
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();

    //Affichage de la fleche rouge qui permet de signaler l'attente d'une action
    sf::VertexArray arrow(sf::Quads, 4);

    if (back) {
        arrow[0].position = sf::Vector2f(485, game.getWindowHeight() - 62);
        arrow[1].position = sf::Vector2f(505, game.getWindowHeight() - 62);
        arrow[2].position = sf::Vector2f(505, game.getWindowHeight() - 50);
        arrow[3].position = sf::Vector2f(485, game.getWindowHeight() - 50);
    }
    else {
        arrow[0].position = sf::Vector2f(465, game.getWindowHeight() - 112);
        arrow[1].position = sf::Vector2f(485, game.getWindowHeight() - 112);
        arrow[2].position = sf::Vector2f(485, game.getWindowHeight() - 100);
        arrow[3].position = sf::Vector2f(465, game.getWindowHeight() - 100);
    }

    arrow[0].texCoords = sf::Vector2f(544, 59);
    arrow[1].texCoords = sf::Vector2f(554, 59);
    arrow[2].texCoords = sf::Vector2f(554, 65);
    arrow[3].texCoords = sf::Vector2f(544, 65);


    target.draw(arrow, states);
}

void Fight::drawFrontPokemon(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setCharacterSize(18);
    text.setColor(sf::Color::Black);

    //Dessin des infos du pokemon
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();
    sf::VertexArray frontMenu(sf::Quads, 4);
    frontMenu[0].position = sf::Vector2f(40, 190);
    frontMenu[1].position = sf::Vector2f(298, 190);
    frontMenu[2].position = sf::Vector2f(298, 276);
    frontMenu[3].position = sf::Vector2f(40, 276);

    frontMenu[0].texCoords = sf::Vector2f(0, 0);
    frontMenu[1].texCoords = sf::Vector2f(104, 0);
    frontMenu[2].texCoords = sf::Vector2f(104, 33);
    frontMenu[3].texCoords = sf::Vector2f(0, 33);

    target.draw(frontMenu, states);

    //Dessin du pokemon en haut
    states.texture = &ResourceManager::GetInstance().getPokemonsTileset();
    sf::VertexArray frontPokemon(sf::Quads, 4);
    frontPokemon[0].position = sf::Vector2f(260, 220);
    frontPokemon[1].position = sf::Vector2f(510, 220);
    frontPokemon[2].position = sf::Vector2f(510, 470);
    frontPokemon[3].position = sf::Vector2f(260, 470);

    const int *frontCoord = this->front->getCoordFace();
    frontPokemon[0].texCoords = sf::Vector2f(frontCoord[0], frontCoord[1]);
    frontPokemon[1].texCoords = sf::Vector2f(frontCoord[2], frontCoord[1]);
    frontPokemon[2].texCoords = sf::Vector2f(frontCoord[2], frontCoord[3]);
    frontPokemon[3].texCoords = sf::Vector2f(frontCoord[0], frontCoord[3]);

    text.setString(front->getName());
    text.setPosition(60, 208);
    target.draw(text);

    text.setString("Niv " + std::to_string(front->getLevel()));
    text.setPosition(205, 208);
    target.draw(text);

    target.draw(frontPokemon, states);
}

void Fight::drawBackPokemon(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setCharacterSize(18);
    text.setColor(sf::Color::Black);

    //Dessin des infos du pokemon
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();
    sf::VertexArray backMenu(sf::Quads, 4);
    backMenu[0].position = sf::Vector2f(250, 440);
    backMenu[1].position = sf::Vector2f(520, 440);
    backMenu[2].position = sf::Vector2f(520, 544);
    backMenu[3].position = sf::Vector2f(250, 544);

    backMenu[0].texCoords = sf::Vector2f(0, 40);
    backMenu[1].texCoords = sf::Vector2f(110, 40);
    backMenu[2].texCoords = sf::Vector2f(110, 82);
    backMenu[3].texCoords = sf::Vector2f(0, 82);

    target.draw(backMenu, states);

    //Dessin du pokemon en bas
    states.texture = &ResourceManager::GetInstance().getPokemonsTileset();
    sf::VertexArray backPokemon(sf::Quads, 4);
    backPokemon[0].position = sf::Vector2f(10, 392);
    backPokemon[1].position = sf::Vector2f(260, 392);
    backPokemon[2].position = sf::Vector2f(260, 642);
    backPokemon[3].position = sf::Vector2f(10, 642);

    const int *backCoord = this->back->getCoordDos();
    backPokemon[0].texCoords = sf::Vector2f(backCoord[0], backCoord[1]);
    backPokemon[1].texCoords = sf::Vector2f(backCoord[2], backCoord[1]);
    backPokemon[2].texCoords = sf::Vector2f(backCoord[2], backCoord[3]);
    backPokemon[3].texCoords = sf::Vector2f(backCoord[0], backCoord[3]);

    text.setString(back->getName());
    text.setPosition(290, 458);
    target.draw(text);

    text.setString("Niv " + std::to_string(back->getLevel()));
    text.setPosition(435, 458);
    target.draw(text);

    text.setString(std::to_string(back->getHp()) + " sur " + std::to_string(back->getHpMax()));
    text.setPosition(390, 502);
    target.draw(text);

    target.draw(backPokemon, states);
}

void Fight::drawPlayer(sf::RenderTarget &target, sf::RenderStates states) const {
        states.texture = &ResourceManager::GetInstance().getPersoTileset();
        sf::VertexArray perso(sf::Quads, 4);
        perso[0].position = sf::Vector2f(100, 488);
        perso[1].position = sf::Vector2f(244, 488);
        perso[2].position = sf::Vector2f(244, 644);
        perso[3].position = sf::Vector2f(100, 644);

        perso[0].texCoords = sf::Vector2f(20,414);
        perso[1].texCoords = sf::Vector2f(68,414);
        perso[2].texCoords = sf::Vector2f(68,466);
        perso[3].texCoords = sf::Vector2f(20,466);

        target.draw(perso, states);
}

void Fight::setHPBar(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();
    sf::VertexArray HPBar(sf::Quads, 4);
    sf::VertexArray yellowHPBar(sf::Quads, 4);
    sf::VertexArray redHPBar(sf::Quads, 4);

    //Yellow HP Sprite
    yellowHPBar[0].texCoords = sf::Vector2f(120, 14);
    yellowHPBar[1].texCoords = sf::Vector2f(123, 14);
    yellowHPBar[2].texCoords = sf::Vector2f(123, 15);
    yellowHPBar[3].texCoords = sf::Vector2f(120, 15);

    //Red HP Sprite
    redHPBar[0].texCoords = sf::Vector2f(120, 18);
    redHPBar[1].texCoords = sf::Vector2f(123, 18);
    redHPBar[2].texCoords = sf::Vector2f(123, 19);
    redHPBar[3].texCoords = sf::Vector2f(120, 19);

    //Gris HP Sprite
    HPBar[0].texCoords = sf::Vector2f(120, 21);
    HPBar[1].texCoords = sf::Vector2f(123, 21);
    HPBar[2].texCoords = sf::Vector2f(123, 23);
    HPBar[3].texCoords = sf::Vector2f(120, 23);

    if (front->getHp() != 0 && front->getHp() != front->getHpMax()) {
        //Front Pokemon
        int frontXpos = 143 + (( 120 * front->getHp() ) / front->getHpMax());
        HPBar[0].position = sf::Vector2f(frontXpos, 242);
        HPBar[1].position = sf::Vector2f(263, 242);
        HPBar[2].position = sf::Vector2f(263, 250);
        HPBar[3].position = sf::Vector2f(frontXpos, 250);

        target.draw(HPBar, states);

        if (front->getHp() <= (front->getHpMax() / 3)) {
            redHPBar[0].position = sf::Vector2f(143, 242);
            redHPBar[1].position = sf::Vector2f(frontXpos, 242);
            redHPBar[2].position = sf::Vector2f(frontXpos, 250);
            redHPBar[3].position = sf::Vector2f(143, 250);

            target.draw(redHPBar, states);
        }
        else if (front->getHp() <= (front->getHpMax() / 2)) {
            yellowHPBar[0].position = sf::Vector2f(143, 242);
            yellowHPBar[1].position = sf::Vector2f(frontXpos, 242);
            yellowHPBar[2].position = sf::Vector2f(frontXpos, 250);
            yellowHPBar[3].position = sf::Vector2f(143, 250);

            target.draw(yellowHPBar, states);
        }
    }

    if (back->getHp() != 0 && back->getHp() != back->getHpMax()) {
        //Back Pokemon
        int backXpos = 373 + (( 120 * back->getHp() ) / back->getHpMax());
        HPBar[0].position = sf::Vector2f(backXpos, 492);
        HPBar[1].position = sf::Vector2f(493, 492);
        HPBar[2].position = sf::Vector2f(493, 500);
        HPBar[3].position = sf::Vector2f(backXpos, 500);

        target.draw(HPBar, states);

        if (back->getHp() <= (back->getHpMax() / 3)) {
            redHPBar[0].position = sf::Vector2f(373, 492);
            redHPBar[1].position = sf::Vector2f(backXpos, 492);
            redHPBar[2].position = sf::Vector2f(backXpos, 500);
            redHPBar[3].position = sf::Vector2f(373, 500);

            target.draw(redHPBar, states);
        }
        else if (back->getHp() <= (back->getHpMax() / 2)) {
            yellowHPBar[0].position = sf::Vector2f(373, 492);
            yellowHPBar[1].position = sf::Vector2f(backXpos, 492);
            yellowHPBar[2].position = sf::Vector2f(backXpos, 500);
            yellowHPBar[3].position = sf::Vector2f(373, 500);

            target.draw(yellowHPBar, states);
        }
    }
}

void Fight::setXPBar(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = &ResourceManager::GetInstance().getBattleMenuTileset();
    sf::VertexArray XPBar(sf::Quads, 4);

    //Gris HP Sprite
    XPBar[0].texCoords = sf::Vector2f(131, 9);
    XPBar[1].texCoords = sf::Vector2f(134, 9);
    XPBar[2].texCoords = sf::Vector2f(134, 11);
    XPBar[3].texCoords = sf::Vector2f(131, 11);

    float pixelByPrct = (493.f - 336.f) / 100.f;
    int backXP = 336 + ( pixelByPrct * back->getPourcentNextLvl());
    XPBar[0].position = sf::Vector2f(backXP, 532);
    XPBar[1].position = sf::Vector2f(336, 532);
    XPBar[2].position = sf::Vector2f(336, 537);
    XPBar[3].position = sf::Vector2f(backXP, 537);

    target.draw(XPBar, states);
}

void Fight::writeTextMenu(sf::RenderTarget &target, sf::RenderStates states) const {
    Game &game = Game::GetInstance();
    PlayerEntity &player = PlayerEntity::getInstance();
    sf::Text text;
    std::string text1 = "";
    std::string text2 = "";
    std::string text3 = "";
    std::string text4 = "";

    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    if (menu == -1) {
        text1 = "ATTAQUE";
        text2 = "SAC";
        text3 = "POKEMON";
        text4 = "FUITE";
    }
    if (menu == 0) {
        if (back->getAttacks().size() > 0)
            text1 = back->getAttacks()[0]->GetName();
        if (back->getAttacks().size() > 1)
            text2 = back->getAttacks()[1]->GetName();
        if (back->getAttacks().size() > 2)
            text3 = back->getAttacks()[2]->GetName();
        if (back->getAttacks().size() > 3)
            text4 = back->getAttacks()[3]->GetName();
    }
    if (menu == 1) {
        std::map< Object*, int >::const_iterator ptr;
        int i = 0;

        ptr = player.getBag()->getInventaire().begin();
        while (ptr != player.getBag()->getInventaire().end())
        {
            if (i == firstSelector)
                text1 = (*ptr).first->getName() + " x" + std::to_string((*ptr).second);
            else if (i == firstSelector + 1)
                text2 = (*ptr).first->getName() + " x" + std::to_string((*ptr).second);
            else if (i == firstSelector + 2)
                text3 = (*ptr).first->getName() + " x" + std::to_string((*ptr).second);
            else if (i == firstSelector + 3)
                text4 = (*ptr).first->getName() + " x" + std::to_string((*ptr).second);
            ++ptr;
            ++i;
        }
        if (i > firstSelector + 3 )
            this->drawRedArrow(target, states, 1);
    }
    if (menu == 2) {
        std::vector<Pokemon *> pokemons = player.getPokemons();
        if (pokemons.size() > firstSelector)
            text1 = pokemons[firstSelector]->getName();
        if (pokemons.size() > firstSelector + 1)
            text2 = pokemons[firstSelector + 1]->getName();
        if (pokemons.size() > firstSelector + 2)
            text3 = pokemons[firstSelector + 2]->getName();
        if (pokemons.size() > firstSelector + 3)
            text4 = pokemons[firstSelector + 3]->getName();
        if (pokemons.size() > firstSelector + 3 )
            this->drawRedArrow(target, states, 1);
    }

    text.setString(text1);
    text.setPosition(70, game.getWindowHeight() - 150);
    text.setCharacterSize(27);
    text.setColor(sf::Color::Black);
    target.draw(text);
    text.setString(text2);
    text.setPosition(300, game.getWindowHeight() - 150);
    target.draw(text);
    text.setString(text3);
    text.setPosition(70, game.getWindowHeight() - 80);
    target.draw(text);
    text.setString(text4);
    text.setPosition(300, game.getWindowHeight() - 80);
    target.draw(text);
}

void Fight::writeTextBegin(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString("Un " + front->getName() + " sauvage apparait...");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextEnd(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString("Tous vos pokemons sont morts !");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextGiveXP(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString(back->getName() + " gagne " + std::to_string(this->getxpGive()) + " XP");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextLevelUp(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString(back->getName() + " passe au niveau " + std::to_string(back->getLevel()) + ".");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextDead(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    if(this->front->getHp() > 0)
        text.setString(this->back->getName() +  " est K.O");
    else
        text.setString(this->front->getName() +  " est K.O");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextCatchFail(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString("La capture de " + this->front->getName() +  " a echoue.");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextCatchOk(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString("Vous avez capture " + this->front->getName() + ".");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextTeamFull(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    text.setString("Votre equipe est deja complete.");
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::writeTextAction(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Text text;
    Game &game = Game::GetInstance();
    text.setFont(*(&ResourceManager::GetInstance().getMainFont()));
    if (state == FIRST_ACTION)
        text.setString(firstAction->getText());
    else if (state == SECOND_ACTION)
        text.setString(secondAction->getText());
    text.setPosition(25, game.getWindowHeight() - 150);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);
    target.draw(text);
}

void Fight::prepareAttack(Attack* atk){
    int random = 0;
    Attack* attackEnemy = this->front->getRandomAttack();

    //Choix Premier attaquant
    srand(time(NULL));
    random = rand()%2;

    //Back pokemon commence
    if(random == 0) {
        this->firstAction = new Action(atk, this->back, this->front, 0);
        this->secondAction = new Action(attackEnemy, this->front, this->back, 1);
    }
    //Front pokemon commence
    else {
        this->firstAction = new Action(attackEnemy, this->front, this->back, 1);
        this->secondAction = new Action(atk, this->back, this->front, 0);
    }
    //Passage à l'état action
    this->state = FIRST_ACTION;
}

void Fight::prepareObject() {
    Attack* attackEnemy = this->front->getRandomAttack();
    PlayerEntity &player = PlayerEntity::getInstance();

    this->firstAction = new Action(player.getBag()->getItem(selector), this->back, this->front);
    this->secondAction = new Action(attackEnemy, this->front, this->back, 1);

    //incrémentation du nombre d'objets utilisés
    nbObjectUsed++;

    //Passage à l'état action
    this->state = FIRST_ACTION;
}

void Fight::prepareNewPokemon(Pokemon *pokemon) {
    Attack* attackEnemy = this->front->getRandomAttack();

    this->firstAction = new Action(pokemon, this->back);
    this->secondAction = new Action(attackEnemy, this->front, pokemon, 1);

    //Passage à l'état action
    this->state = FIRST_ACTION;
}

void Fight::prepareToRun() {
    int random = 0;
    Attack* attackEnemy = this->front->getRandomAttack();


    this->firstAction = new Action(this->back);
    this->secondAction = new Action(attackEnemy, this->front, this->back, 1);

    //Passage à l'état action
    this->state = FIRST_ACTION;
}

void Fight::launchAction() {
    Game &game = Game::GetInstance();

    if (state == FIRST_ACTION) {
        firstAction->launch(this);
    }
    else if (state == SECOND_ACTION) {
        secondAction->launch(this);
        menu = -1;
    }
}

void Fight::pokemonDie() {
    PlayerEntity &pm = PlayerEntity::getInstance();

    if(front->getHp() == 0) {
        state = GIVE_XP;
        this->xpGive = front->getXp();
        //TODO:Free des variables
    }
    else {
        if(pm.hasPokemonAlive()){
            state = CHOOSE_ACTION;
            this->menu = 2;
        }else{
            pm.resetDied();
            pm.TeamDied();
            state = END;
        }
    }
}

void Fight::setBack(Pokemon *back) {
    Fight::back = back;
}

void Fight::Notify(char entry) {
    Game &game = Game::GetInstance();
    PlayerEntity &player = PlayerEntity::getInstance();
    switch (entry) {
        case ('Z'):
            if (this->selector > 1)
                this->selector -= 2;
            if (this->firstSelector != 0)
                this->firstSelector -= 2;
            break;
        case ('S'):
            if (this->selector < 2)
                this->selector += 2;
            else if(menu == 1) {
                if (this->selector % 2 == 1 && player.getBag()->getInventaire().size() > this->selector + 1) {
                    firstSelector = selector - 1;
                    selector++;
                }
                else if (this->selector % 2 == 0 && player.getBag()->getInventaire().size() > this->selector + 2 ) {
                    firstSelector = selector;
                    selector += 2;
                }
            }
            else if (menu == 2) {
                if (this->selector % 2 == 1 && player.getPokemons().size() > this->selector + 1) {
                    firstSelector = selector - 1;
                    selector++;
                }
                else if (this->selector % 2 == 0 && player.getPokemons().size() > this->selector + 2 ) {
                    firstSelector = selector;
                    selector += 2;
                }
            }
            break;
        case ('Q'):
            if (this->selector % 2 == 1)
                this->selector--;
            break;
        case ('D'):
            if (this->selector % 2 == 0)
                this->selector++;
            break;
        case ('E'):
            //En fonction de l'état du jeu
            switch(state) {
                case (BEGIN):
                    state = CHOOSE_ACTION;
                    break;
                case (CHOOSE_ACTION):
                    //En fonction du menu dans lequel on se trouve
                    switch(menu) {
                        case (-1) :
                            //Changement de menu vers celui selectionné
                            menu = selector;
                            //Si option FUITE est choisie alors fin du combat
                            if (selector == 3)
                                prepareToRun();
                            break;
                        case (0) :
                            //Si on choisit une attaque valide alors on prepare les actions du tour
                            if (back->getAttacks().size() > selector) {
                                this->prepareAttack(back->getAttacks()[selector]);
                            }
                            break;
                        case (1) :
                            //Si on choisit un objet valide alors on prepare les actions du tour
                            if (player.getBag()->getInventaire().size() > selector && this->nbObjectUsed < this->nbMaxObject) {
                                this->prepareObject();
                            }
                            break;
                        case (2) :
                            //Si on choisit un pokemon valide alors on prepare les actions du tour
                            if (player.getPokemons().size() > selector && player.getPokemons()[selector] != this->back && player.getPokemons()[selector]->getHp() > 0) {
                                this->prepareNewPokemon(player.getPokemons()[selector]);
                            }
                            break;
                        default:
                            break;
                        }
                    break;
                case (FIRST_ACTION):
                case (SECOND_ACTION):
                    this->launchAction();
                    break;
                case (CATCH_FAIL):
                    this->state = SECOND_ACTION;
                    break;
                case (CATCH_OK):
                    this->catchOk();
                    break;
                case (TEAM_FULL):
                    this->menu = 2;
                    this->state = DELETE_POKEMON;
                    break;
                case (DELETE_POKEMON):
                    if (menu == 2 && player.getPokemons().size() > selector) {
                        player.changePokemon(selector, front);
                        Game::GetInstance().setState(WORLD);
                    }
                    break;
                case (DEAD):
                    pokemonDie();
                    break;
                case (GIVE_XP):
                    giveXp();
                    break;
                case (LEVEL_UP):
                    back->levelUp();
                    giveXp();
                    break;
                case (END):
                    game.setState(WORLD);
                    break;
                default:
                    break;
            }
            selector = 0;
            firstSelector = 0;
            break;
        case ('R'):
            //EN cas de 'retour' on affiche le menu principal si notre pokemon n'est pas mort et si ce n'est pas un remplacement de pokemon
            if (this->back->getHp() > 0 && this->state != DELETE_POKEMON)
                menu = -1;
            selector = 0;
            firstSelector = 0;
            break;
        default:
            break;
    }
}

void Fight::free() {
    delete firstAction;
    delete secondAction;
}

void Fight::catchOk() {
    PlayerEntity &pm = PlayerEntity::getInstance();
    //TODO : Verif si + 6 Pokemon
    if(pm.getPokemons().size() < 6){
        pm.addPokemon(front);
        Game::GetInstance().setState(WORLD);
    }
    else{
        this->state = TEAM_FULL;
    }
}

int Fight::getxpGive() const {
    return (this->xpGive);
}

void Fight::giveXp() {
    int xpForNextLevel = back->getXpForNextLevel();
    int xpNeedForUp = xpForNextLevel - back->getXpInLevel();
    if (this->xpGive >= xpNeedForUp){
        back->giveXp(xpNeedForUp);
        this->xpGive -= xpNeedForUp;
        this->state = LEVEL_UP;
    }else{
        back->giveXp(this->xpGive);
        this->xpGive = 0;
        Game::GetInstance().setState(WORLD);
    }

}
