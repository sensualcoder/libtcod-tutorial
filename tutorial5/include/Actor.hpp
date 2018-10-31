#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>

#include <libtcod/libtcod.hpp>

namespace tcodtutorial
{
    class Actor
    {
        public:
            Actor(int x, int y, int cha, std::string name, const TCODColor& color);

            void Render() const;

            int GetX() const;
            int GetY() const;
            std::string GetName() const;

            void SetPos(int x, int y);

            virtual void Update() {}

        protected:
            int PosX, PosY;
            int Char;
            std::string Name;
            TCODColor Color;
    };

    class Enemy : public Actor
    {
        public:
            Enemy(int x, int y, int cha, std::string name, const TCODColor& color);

            void Update();
    };
}

#endif
