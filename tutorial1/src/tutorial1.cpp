#include "libtcod/libtcod.hpp"

int main()
{
    int playerX = 40,
        playerY = 25;

    TCODConsole::initRoot(80, 50, "libtcod C++ tutorial 1");

    while(!TCODConsole::isWindowClosed() )
    {
        TCOD_key_t key;

        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

        switch(key.vk)
        {
            case TCODK_UP:
                --playerY;
                break;
            case TCODK_DOWN:
                ++playerY;
                break;
            case TCODK_LEFT:
                --playerX;
                break;
            case TCODK_RIGHT:
                ++playerX;
                break;
            default:
                break;
        }

        TCODConsole::root->clear();
        TCODConsole::root->putChar(playerX, playerY, '@');
        TCODConsole::root->flush();
    }

    return 0;
}