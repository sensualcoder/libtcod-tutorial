#include "Actor.hpp"

namespace tcodtutorial
{
    Actor::Actor(int x, int y, int cha, std::string name, const TCODColor& color) 
        : PosX(x), PosY(y), Char(cha), Name(name), Color(color)
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

    std::string Actor::GetName() const
    {
        return this->Name;
    }

    void Actor::SetPos(int x, int y)
    {
        this->PosX = x;
        this->PosY = y;
    }

    Enemy::Enemy(int x, int y, int cha, std::string name, const TCODColor& color)
                : Actor(x, y, cha, name, color)
    {
    }

    void Enemy::Update()
    {
        printf("The %s growls!\n", this->Name.c_str() );
    }
}