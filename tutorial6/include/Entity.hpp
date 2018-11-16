#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>

#include <libtcod/libtcod.hpp>

#include "AI.hpp"
#include "Attacker.hpp"
#include "Destructible.hpp"
#include "Point.hpp"
#include "Subject.hpp"

namespace tcodtutorial
{
    class Entity : public Subject
    {
        public:
            Entity(Point point, int cha, std::string name, const TCODColor& color);

            void Render() const;

            int GetX() const;
            int GetY() const;
            std::string GetName() const;

            void SetPos(Point point);

            void SetAI(AI* ai = nullptr);
            void SetAttacker(Attacker* attacker = nullptr);
            void SetDestructible(Destructible* destructible = nullptr);

            virtual void Update() = 0;

        protected:
            int PosX, PosY;
            int Char;
            bool IsBlocker;
            
            std::string Name;
            TCODColor Color;

            std::unique_ptr<AI> EntityAI;
            std::unique_ptr<Attacker> Attack; 
            std::unique_ptr<Destructible> Destruct;
    };

    class Player : public Entity
    {
        public:
            Player(Point point, int cha, std::string name, const TCODColor& color);

            void Update();
    };

    class NPC : public Entity
    {
        public:
            NPC(Point point, int cha, std::string name, const TCODColor& color);

            void Update();
    };
}

#endif
