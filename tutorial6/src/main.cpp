#include <libtcod/libtcod.hpp>

#include "Engine.hpp"

int main()
{
    tcodtutorial::Engine engine;

    while(!TCODConsole::isWindowClosed() )
    {
        engine.Update();
        engine.Render();

        TCODConsole::root->flush();
    }

    return 0;
}