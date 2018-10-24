#include "libtcod/libtcod.hpp"

#include "Engine.hpp"

namespace tcodtutorial
{
    class Engine;
}

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