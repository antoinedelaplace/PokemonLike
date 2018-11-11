//
// Created by root on 4/26/17.
//

#include "ListObjects.hh"

ListObjects* ListObjects::instance = new ListObjects();

ListObjects& ListObjects::GetInstance(){
    return *instance;
}

ListObjects::ListObjects(){
    //Lecture de csv
    std::ifstream file ("houvet_b/resources/datas/ListObjects.csv");
    std::string value;

    while ( file.good() ) {
        getline ( file, value, ',' );
        this->listObject.push_back(ObjectFactory::Create(value));
    }
}

ListObjects::~ListObjects(){
}

Object*	ListObjects::GetObjectByName(std::string name) const{
    std::list<Object *> m_list = this->GetInstance().listObject;
    std::list<Object *>::iterator ptr;

    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        if ((*ptr)->getName().compare(name) == 0)
            return (*ptr);
        ++ptr;
    }
    return NULL;
}

Object*    ListObjects::GetObjectRandom() const{
    std::list<Object *> m_list = this->GetInstance().listObject;
    std::list<Object *>::iterator ptr;
    int i = 0;
    int random = 0;

    srand(time(NULL));
    random = rand()%m_list.size();

    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        if (i == random){
            return ((*ptr));
        }
        ++ptr;
        i++;
    }
    return NULL;
}

void ListObjects::free() {
    std::list<Object *> m_list = ListObjects::GetInstance().listObject;
    std::list<Object *>::iterator ptr;
    ptr = m_list.begin();
    while (ptr != m_list.end())
    {
        delete (*ptr);
        ++ptr;
    }
    delete instance;
}

