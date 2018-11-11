//
// Created by Romain on 31/03/2017.
//

#include "ListPokemon.hh"

ListPokemon* ListPokemon::instance = new ListPokemon();

ListPokemon& ListPokemon::GetInstance() {
    return *instance;
}

ListPokemon::ListPokemon(){
    this->listPokemon.clear();
}

ListPokemon::~ListPokemon(){
}

void	ListPokemon::Start(){

    ListAttack &la = ListAttack::GetInstance();
    //Lecture de csv
    std::ifstream file ("houvet_b/resources/datas/ListPokemon.csv");
    std::string value;
    std::string value2;

    while ( file.good() ) {
        Pokemon* tmp = new Pokemon();
        //Name
        getline ( file, value, ';' );
        tmp->setName(value);
        //Atk
        getline ( file, value, ';' );
        tmp->setAtk(atoi(value.c_str()));
        //Def
        getline ( file, value, ';' );
        tmp->setDef(atoi(value.c_str()));
        //faceAx
        getline ( file, value, ';' );
        tmp->addCoordFace(atoi(value.c_str()), 0);
        //faceAy
        getline ( file, value, ';' );
        tmp->addCoordFace(atoi(value.c_str()), 1);
        //faceBx
        getline ( file, value, ';' );
        tmp->addCoordFace(atoi(value.c_str()), 2);
        //faceBy
        getline ( file, value, ';' );
        tmp->addCoordFace(atoi(value.c_str()), 3);
        //dosAx
        getline ( file, value, ';' );
        tmp->addCoordDos(atoi(value.c_str()), 0);
        //dosAy
        getline ( file, value, ';' );
        tmp->addCoordDos(atoi(value.c_str()), 1);
        //dosBx
        getline ( file, value, ';' );
        tmp->addCoordDos(atoi(value.c_str()), 2);
        //dosBy
        getline ( file, value, ';' );
        tmp->addCoordDos(atoi(value.c_str()), 3);
        //hpmax
        getline ( file, value, ';' );
        tmp->setHpMax(atoi(value.c_str()));
        tmp->setHp(atoi(value.c_str()));
        //xplevelone
        getline ( file, value, ';' );
        tmp->setXpLevelOne(atoi(value.c_str()));
        //xp et xpmax
        tmp->setXp(0);
        tmp->setXpMax(tmp->getXpLevel(100));
        //Ajout des 2 attacks de base
        getline ( file, value, ';' );
        tmp->addAttack(la.GetAttackByName(value.c_str()));
        getline ( file, value, ';' );
        tmp->addAttack(la.GetAttackByName(value.c_str()));

        this->GetInstance().listPokemon.push_back(tmp);
    }
}

Pokemon*	ListPokemon::GetPokemonByName(std::string name) const{
    std::list<Pokemon *> m_list = this->GetInstance().listPokemon;
    std::list<Pokemon *>::iterator ptr;

    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        if ((*ptr)->getName().compare(name) == 0)
            return (new Pokemon(*ptr));
        ++ptr;
    }
    return NULL;
}

Pokemon*    ListPokemon::GetPokemonRandom() const{
    std::list<Pokemon *> m_list = this->GetInstance().listPokemon;
    std::list<Pokemon *>::iterator ptr;
    int i = 0;
    int random = 0;

    srand(time(NULL));
    random = rand()%m_list.size();

    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        if (i == random){

            Pokemon* newPokemon = new Pokemon((*ptr));//(*ptr)->getName(), (*ptr)->getAtk(), (*ptr)->getDef(), (*ptr)->getXp(), (*ptr)->getXpMax(), (*ptr)->getHp(), (*ptr)->getHpMax(), (*ptr)->getCoordFace(), (*ptr)->getCoordDos());
            return (newPokemon);
        }
        ++ptr;
        i++;
    }
    return NULL;
}

void ListPokemon::free() {

    std::list<Pokemon *> m_list = ListPokemon::GetInstance().listPokemon;
    std::list<Pokemon *>::iterator ptr;
    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        delete (*ptr);
        ++ptr;
    }
    delete instance;
}
