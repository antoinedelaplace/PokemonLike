#include "Action.hh"

Action::Action(Attack *attack, Pokemon *launcher, Pokemon *target, int isSauvage) {
    this->attack = attack;
    this->launcher = launcher;
    this->target = target;
    this->isSauvage = isSauvage;
    this->type = ATTACK;
}

Action::Action(Pokemon *newPokemon, Pokemon *launcher) {
    this->newPokemon = newPokemon;
    this->launcher = launcher;
    this->type = NEW_POKEMON;
}

Action::Action(Object *object, Pokemon *launcher, Pokemon *target) {
    this->object = object;
    this->launcher = launcher;
    this->target = target;
    this->type = USE_OBJECT;
}

Action::Action(Pokemon *runner) {
    this->launcher = runner;
    this->type = TRY_RUN;
    int random = 0;

    //Test de la fuite
    srand(time(NULL));
    random = rand()%2;
    if(random == 0) {
        this->run = 0;
    }
    else {
        this->run = 1;
    }
}

std::string Action::getText() const {
    switch (type) {
        case (ATTACK) :
            if (isSauvage)
                return (this->launcher->getName() + " sauvage utilise " + this->attack->GetName());
            else
                return (this->launcher->getName() + " utilise " + this->attack->GetName());
            break;
        case (NEW_POKEMON) :
            return ( this->newPokemon->getName() + " remplace " + this->launcher->getName());
            break;
        case (USE_OBJECT) :
            return (this->launcher->getName() + " utilise " + this->object->getName());
            break;
        case (TRY_RUN) :
            if (run)
                return ("Vous prenez la fuite ...");
            else
                return ("Fuite impossible");
            break;
        default:
            break;
    }
}

void Action::launch(Fight *fight) {
    int catchReturn;
    FightState stateBefore;
    stateBefore = fight->state;

    switch (type) {
        case (ATTACK) :
            this->launcher->hit(this->attack, this->target);
            if(fight->getFront()->getHp() == 0 || fight->getBack()->getHp() == 0){
                fight->state = DEAD;
            }
            else {
                if (stateBefore == FIRST_ACTION){
                    fight->state = SECOND_ACTION;
                }
                else{
                    fight->state = CHOOSE_ACTION;
                }
            }
            break;
        case (NEW_POKEMON):
            fight->setBack(this->newPokemon);
            fight->state = SECOND_ACTION;
            break;
        case (TRY_RUN):
            if (run)
            Game::GetInstance().setState(WORLD);
            else
            fight->state = SECOND_ACTION;
            break;
        case (USE_OBJECT) :
            catchReturn = this->object->Use(this->launcher, this->target);
            if (catchReturn == 0){
                //TODO : State capture fail
                fight->state = CATCH_FAIL;
            }else if (catchReturn == 1){
                fight->state = CATCH_OK;
            }else{
                fight->state = SECOND_ACTION;
            }
            break;
        default:
            break;
    }

}
