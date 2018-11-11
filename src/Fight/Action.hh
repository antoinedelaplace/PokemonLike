//
// Created by Antoine on 26/04/2017.
//

#ifndef FIRST_ACTION_HH
#define FIRST_ACTION_HH


#include "../Entity/Pokemon.hh"
#include "../Object/Object.hh"
#include "Fight.hh"
class Fight;

enum ActionType { ATTACK, NEW_POKEMON, USE_OBJECT, TRY_RUN };

class Action {
public:
    std::string getText() const;
    Action(Attack *attack, Pokemon *launcher, Pokemon *target, int isSauvage);
    Action(Pokemon *newPokemon, Pokemon *launcher);
    Action(Object *object, Pokemon *launcher, Pokemon *target);
    Action(Pokemon *runner);
    void launch(Fight *fight);

private:
    ActionType type;
    Pokemon *launcher;
    Pokemon *target;
    bool isSauvage;
    bool run;

    Attack *attack;
    Pokemon *newPokemon;
    Object *object;
};


#endif //FIRST_ACTION_HH
