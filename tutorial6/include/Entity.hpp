#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>

#include <libtcod/libtcod.hpp>

#include "GameState.hpp"
#include "Point.hpp"
#include "Subject.hpp"

#include "Components/AiComponent.hpp"
#include "Components/AttackerComponent.hpp"
#include "Components/DestructibleComponent.hpp"

namespace tcodtutorial
{
    class Entity : public Subject
    {
        public:
            Entity(Point point, int displaycharacter, std::string name, const TCODColor& color);

            void Render() const;

            Point GetPos() const;
            int GetX() const;
            int GetY() const;
            std::string GetName() const;

            void SetPos(Point point);

            void SetAI(AiComponent* ai = nullptr);
            void SetAttacker(AttackerComponent* attacker = nullptr);
            void SetDestructible(DestructibleComponent* destructible = nullptr);

            virtual void Update(World& world) = 0;

        protected:
            Point position_;
            int displaycharacter_;
            bool isblocker_;
            
            std::string name_;
            TCODColor color_;

            std::unique_ptr<AiComponent> ai_;
            std::unique_ptr<AttackerComponent> attacker_; 
            std::unique_ptr<DestructibleComponent> destructible_;
    };

    class Player : public Entity
    {
        public:
            Player(Point point, int cha, std::string name, const TCODColor& color);

            void Update(World& world);
    };

    class NPC : public Entity
    {
        public:
            NPC(Point point, int cha, std::string name, const TCODColor& color, AiComponent* ai);

            void Update(World& world);
    };
}

#endif
