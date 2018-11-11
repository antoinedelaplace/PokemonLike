//
// Created by Romain on 31/03/2017.
//

#include "Pokemon.hh"

Pokemon::Pokemon() {
}

Pokemon::~Pokemon(){
}

Pokemon::Pokemon(Pokemon* pokemon){
    int random = 0;
    this->setName(pokemon->getName());
    this->setAtk(pokemon->getAtk());
    this->setDef(pokemon->getDef());
    this->setHp(pokemon->getHp());
    this->setHpMax(pokemon->getHpMax());
    this->setXpMax(pokemon->getXpMax());
    this->setXpLevelOne(pokemon->getXpLevelOne());
    srand(time(NULL));
    random = 20+(rand()%80);

    this->setXp(random);
    for(int i(0); i < this->getLevel(); i++){
        this->levelUp();
    }
    for ( int i(0); i < 4; i++){
        this->addCoordFace(pokemon->coordFace[i], i);
        this->addCoordDos(pokemon->coordDos[i], i);
    }
    std::vector<Attack *>::iterator ptr;

    ptr = pokemon->Attacks.begin();
    while (ptr != pokemon->Attacks.end())
    {
        this->addAttack((*ptr));
        ++ptr;
    }

}

void Pokemon::setXpLevelOne(int val){
    this->xpLvlOne = val;
}

int Pokemon::getXpLevelOne() const{
    return (this->xpLvlOne);
}

int Pokemon::getXpLevel(int level) const{
    int xpForLvl;
    int xpForNext;
    float coefXp;

    xpForLvl = this->getXpLevelOne();
    for (int i(1); i <= level ;i++){
        if (i == level)
            return xpForLvl;
        if (i < 2){
            coefXp = 1;
        }else if(i < 3){
            coefXp = 0.7;
        }else if(i < 6){
            coefXp = 0.4;
        }else if(i < 10){
            coefXp = 0.3;
        }else if(i < 20){
            coefXp = 0.25;
        }else if(i < 30){
            coefXp = 0.2;
        }else if(i < 70){
            coefXp = 0.1;
        }else if(i < 100){
            coefXp = 0.05;
        }
        xpForNext = xpForLvl * coefXp;
        if (xpForNext < 1)
            xpForNext = 1;
        xpForLvl += xpForNext;
    }
    return (0);
}

void Pokemon::setName(std::string name){
    this->name = name;
}

void Pokemon::setAtk(int atk){
    this->atk = atk;
}

void Pokemon::setDef(int def){
    this->def = def;
}

void Pokemon::addCoordFace(int coord, int index) {
    this->coordFace[index] = coord;
}

void Pokemon::addCoordDos(int coord, int index) {
    this->coordDos[index] = coord;
}

int Pokemon::getLevel() const {
    int lvl;
    int xplvl = 0;
    int lvlNext = 1;
    int xplvlNext = this->getXpLevelOne();

    for(lvl = 0; !((xplvl <= this->getXp()) && (xplvlNext > this->getXp())) ;lvl++){

        xplvl = xplvlNext;
        lvlNext++;
        xplvlNext = this->getXpLevel(lvlNext);
    }
    return (lvl);
}

int Pokemon::getHp() const {
    return hp;
}

int Pokemon::getHpMax() const {
    return hpMax;
}

int Pokemon::getXp() const{
    return this->xp;
}

int Pokemon::getXpMax() const{
    return this->xpmax;
}

int Pokemon::getAtk() const{
    return this->atk;
}

int Pokemon::getDef() const{
    return this->def;
}

const std::string &Pokemon::getName() const {
    return name;
}

const int *Pokemon::getCoordFace() const {
    return coordFace;
}

const int *Pokemon::getCoordDos() const {
    return coordDos;
}

void Pokemon::hit(Attack* atk, Pokemon* cible){
    float coefAtk;
    float coefMax;
    int diffLevel;
    int dmg;
    int res;

    diffLevel = ((this->getLevel() - cible->getLevel()) > 0 ? (this->getLevel() - cible->getLevel()) : 0 );

    if (diffLevel > 0 && diffLevel <= 5)
        coefMax = 0.5;
    else if (diffLevel > 5 && diffLevel <= 8)
        coefMax = 1;
    else
        coefMax = 3;
    res = this->atk * this->getLevel() - cible->def * cible->getLevel();
    if (res <= 0)
        coefAtk = 0;
    else if (res > coefMax)
        coefAtk = coefMax;
    else
        coefAtk = res;
    dmg = atk->getDmg() + ((coefAtk/10.0) * atk->getDmg());
    if (dmg <= 0) dmg = 1;
    int pv_cible = cible->getHp() - dmg;
    if (pv_cible <= 0)
        pv_cible = 0;
    if (((atk->GetName().compare("Vampirisme")) == 0) || ((atk->GetName().compare("Vol Vie")) == 0)){
        this->Heal(dmg);
    }
    cible->setHp(pv_cible);
}

void Pokemon::setXp(int xp){
    this->xp = xp;
}

void Pokemon::setXpMax(int xp){
    this->xpmax = xp;
}

void Pokemon::setHp(int hp){
    this->hp = hp;
}

void Pokemon::setHpMax(int hp){
    this->hpMax = hp;
}

void Pokemon::giveXp(int xp){
    if (this->xp + xp >= this->xpmax)
        this->xp += this->xpmax;
    else
        this->xp += xp;
}

void Pokemon::Heal(int val){
    if (this->hp + val > this->hpMax)
        this->hp = this->hpMax;
    else
        this->hp += val;
}

void Pokemon::addAttack(Attack* atk){
    if (this->Attacks.size() < 4){
        this->Attacks.push_back(new Attack(atk->GetName(), atk->GetDmg()));
    }
}

Attack* Pokemon::getRandomAttack(){
    int random = 0;
    srand(time(NULL));
    random = rand()%this->Attacks.size();
    return (this->Attacks[random]);
}

std::vector<Attack *> Pokemon::getAttacks() const {
    return Attacks;
}

void Pokemon::looseXp(){
    this->xp -= ((this->xp/100)*3);
}

int Pokemon::getXpForNextLevel() const{
    int lvl = this->getLevel();
    return (this->getXpLevel(lvl+1)-this->getXpLevel(lvl));
}

int Pokemon::getXpInLevel() const{
    int xpLvl = this->getXpLevel(this->getLevel());
    int xpForUp = this->getXp() - xpLvl;
    return xpForUp;
}

float Pokemon::getPourcentNextLvl() const{
    int xpForLvl = this->getXpForNextLevel();
    int m_xpMarge = this->getXpInLevel();
    int prctXp = (m_xpMarge * 100)/xpForLvl;
    return prctXp;
}


void Pokemon::levelUp() {
    this->setHpMax(this->getHpMax() + (this->getHpMax() * 0.1));
    this->setHp(this->getHp() + (this->getHp() * 0.1));
}