#include "src/Game.hh"

int main()
{
    if (!Game::GetInstance().start())
        return (-1);
    Game::free();
    return (0);
}