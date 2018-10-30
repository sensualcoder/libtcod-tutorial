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

    class Engine
    {
        public:
            Engine();

            void GenerateMap();

            void Update();
            void Render() const;

        private:
            TCODList<Actor*> Actors;
            std::unique_ptr<Actor> Player;
            std::unique_ptr<Map> GameMap;

            int FovRadius;
            bool ComputeFov;
    };
}

#endif
