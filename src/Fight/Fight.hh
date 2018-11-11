#ifndef FIRST_FIGHT_HH
#define FIRST_FIGHT_HH

#include <SFML/Graphics.hpp>
#include "../Manager/ResourceManager.hh"
#include "../List/ListPokemon.hh"
#include "../Game.hh"
#include "Action.hh"
class Action;

enum FightState { BEGIN, CHOOSE_ACTION, FIRST_ACTION, SECOND_ACTION, DEAD, GIVE_XP, END, CATCH_FAIL, CATCH_OK, TEAM_FULL, DELETE_POKEMON, LEVEL_UP };

class Fight : public sf::Drawable, public sf::Transformable, public IObserver {
public:
    Fight();
    ~Fight();
    virtual void Notify(char entry);
    void free();
    void setBack(Pokemon *back);
    Pokemon* getFront();
    Pokemon* getBack();
    FightState state;
    int getxpGive() const;
    void giveXp();
    //void setState(FightState state);
private:
    Pokemon *front;
    Pokemon *back;
    int firstSelector;
    int selector;
    int menu;
    int xpGive;
    int nbMaxObject;
    int nbObjectUsed;
    Action *firstAction;
    Action *secondAction;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawPlayer(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawBackPokemon(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawFrontPokemon(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChoiceMenu(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawDescriptionMenu(sf::RenderTarget &target, sf::RenderStates states) const;
    void drawRedArrow(sf::RenderTarget &target, sf::RenderStates states, int back) const;
    void writeTextMenu(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextBegin(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextEnd(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextAction(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextDead(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextLevelUp(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextCatchFail(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextCatchOk(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextTeamFull(sf::RenderTarget& target, sf::RenderStates states) const;
    void writeTextGiveXP(sf::RenderTarget& target, sf::RenderStates states) const;
    void setHPBar(sf::RenderTarget& target, sf::RenderStates states) const;
    void setXPBar(sf::RenderTarget& target, sf::RenderStates states) const;
    void prepareAttack(Attack* atk);
    void prepareObject();
    void prepareNewPokemon(Pokemon* pokemon);
    void launchAction();
    void prepareToRun();
    void pokemonDie();
    void catchOk();
};


#endif //FIRST_FIGHT_HH
