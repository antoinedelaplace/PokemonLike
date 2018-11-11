//
// Created by Romain on 31/03/2017.
//

#include "ListAttack.hh"

ListAttack* ListAttack::instance = new ListAttack();

ListAttack& ListAttack::GetInstance(){
    return *instance;
}

ListAttack::ListAttack(){
    this->listAttack.clear();
}

ListAttack::~ListAttack(){
}

void	ListAttack::Start(){
    //Lecture de csv
    std::ifstream file ("houvet_b/resources/datas/ListAttack.csv");
    std::string value;

    while ( file.good() )
    {
        Attack* tmp = new Attack();
        getline ( file, value, ',' );
        tmp->setName(value.c_str());
        getline ( file, value, ',' );
        tmp->setDmg(atoi(value.c_str()));
        this->GetInstance().listAttack.push_back(tmp);
    }
}

Attack*	ListAttack::GetAttackByName(std::string name) const{
    std::list<Attack *> m_list = this->GetInstance().listAttack;
    std::list<Attack *>::iterator ptr;

    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        if ((*ptr)->GetName().compare(name) == 0)
            return (*ptr);
        ++ptr;
    }
    return NULL;
}

void ListAttack::free() {
    std::list<Attack *> m_list = ListAttack::GetInstance().listAttack;
    std::list<Attack *>::iterator ptr;
    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        delete (*ptr);
        ++ptr;
    }
    delete instance;
}
