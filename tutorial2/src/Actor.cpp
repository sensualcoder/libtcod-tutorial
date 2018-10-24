#include "Actor.hpp"

namespace tcodtutorial
{
    Actor::Actor(int posX, int posY, int cha, const TCODColor& color) : PosX(posX), PosY(posY), Char(cha), Color(color)
    {
    }

    void Actor::Render() const
    {
        TCODConsole::root->setChar(this->PosX, this->PosY, this->Char);
        TCODConsole::root->setCharForeground(this->PosX, this->PosY, this->Color);
    }

    int Actor::GetX() const
    {
        return this->PosX;
    }

    int Actor::GetY() const
    {
        return this->PosY;
    }

    void Actor::MoveUp()
    {
        --this->PosY;
    }
    
    void Actor::MoveDown()
    {
        ++this->PosY;
    }
    
    void Actor::MoveLeft()
    {
        --this->PosX;
    }
    
    void Actor::MoveRight()
    {
        ++this->PosX;
    }
}