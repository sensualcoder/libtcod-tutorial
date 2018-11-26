#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <memory>
#include <vector>

namespace tcodtutorial
{
    class Entity;
    class Map;

    using EntityShrPtr = std::shared_ptr<Entity>;

    enum GameState_t
    {
        STARTUP,
        IDLE,
        NEW_TURN,
        VICTORY,
        DEFEAT
    };

    struct World
    {
        const std::vector<EntityShrPtr>& entitylist_;
        Map& map_;
    };
}

#endif
