#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>

#include <libtcod/libtcod.hpp>

#include "Actor.hpp"
#include "Map.hpp"

namespace tcodtutorial
{
    class Actor;
    class Map;

    enum GameState
    {
        STARTUP,
        IDLE,
        NEW_TURN,
        VICTORY,
        DEFEAT
    };

    class Engine
    {
        public:
            Engine();

            void GenerateMap();
            void GenerateMonsters();
            void AddMonster(int x, int y);

            bool MoveOrAttack(int x, int y);

            bool CanWalk(int x, int y) const;

            void Update();
            void Render() const;

        private:
            TCODList<Actor*> Actors;
            std::unique_ptr<Actor> Player;
            std::unique_ptr<Map> GameMap;

            int FovRadius;
            GameState State;
    };
}

#endif
