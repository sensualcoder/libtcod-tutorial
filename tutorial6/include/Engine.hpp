#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>

#include <libtcod/libtcod.hpp>

#include "Entity.hpp"
#include "Event.hpp"
#include "GameState.hpp"
#include "Map.hpp"
#include "Observer.hpp"

namespace tcodtutorial
{
    using EntityShrPtr = std::shared_ptr<Entity>;

    class Engine : public Observer
    {
        public:
            Engine();

            void GenerateMap();
            void GenerateMonsters();
            
            void AddMonster(Point point);
            void ClearEntities();

            bool CanWalk(Point point) const;

            // Implemented from Observer pure virtual method
            void OnNotify(const Entity& entity, Event event);

            void HandleInput();
            void Update();
            void Render() const;

        private:
            std::vector<EntityShrPtr> entitylist_;
            EntityShrPtr playerptr_;
            std::unique_ptr<Map> map_;

            int FovRadius;
            GameState_t State;
    };
}

#endif
