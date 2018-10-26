#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <libtcod/libtcod.hpp>

namespace tcodtutorial
{
    class Actor
    {
        public:
            Actor(int posX, int posY, int cha, const TCODColor& color);

            void Render() const;

            int GetX() const;
            int GetY() const;
            
            void MoveUp();
            void MoveDown();
            void MoveLeft();
            void MoveRight();

            void SetPos(int posX, int posY);

        private:
            int PosX, PosY;
            int Char;
            TCODColor Color;
    };
}

#endif
