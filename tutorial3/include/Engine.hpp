#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>

#include <libtcod/libtcod.hpp>

#include "Actor.hpp"
#include "Map.hpp"

namespace tcodtutorial
{
    class Actor;
    class Map;

    class Engine
    {
        public:
            Engine();

            void Update();
            void Render();

        private:
            TCODList<Actor*> Actors;
            std::unique_ptr<Actor> Player;
            std::unique_ptr<Map> GameMap;
    };
}

#endif
