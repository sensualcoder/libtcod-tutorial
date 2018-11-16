#include "Entity.hpp"

namespace tcodtutorial
{
    Entity::Entity(Point point, int cha, std::string name, const TCODColor& color) 
        : PosX(point.x_), PosY(point.y_), Char(cha), Name(name), Color(color), IsBlocker(true),
          EntityAI(nullptr), Attack(nullptr), Destruct(nullptr)
    {
    }

    void Entity::Render() const
    {
        TCODConsole::root->setChar(PosX, PosY, Char);
        TCODConsole::root->setCharForeground(PosX, PosY, Color);
    }

    int Entity::GetX() const
    {
        return PosX;
    }

    int Entity::GetY() const
    {
        return PosY;
    }

    std::string Entity::GetName() const
    {
        return Name;
    }

    void Entity::SetPos(Point point)
    {
        PosX = point.x_;
        PosY = point.y_;
    }

    void Entity::SetAI(AI* ai)
    {
        ai == nullptr 
            ? EntityAI = std::make_unique<AI>()
            : EntityAI = std::unique_ptr<AI>(ai);
    }

    void Entity::SetAttacker(Attacker* attacker)
    {
        attacker == nullptr 
            ? Attack = std::make_unique<Attacker>()
            : Attack = std::unique_ptr<Attacker>(attacker);
    }
    
    void Entity::SetDestructible(Destructible* destructible)
    {
        destructible == nullptr
            ? Destruct = std::make_unique<Destructible>()
            : Destruct = std::unique_ptr<Destructible>(destructible);
    }

    // Derived Player class
    Player::Player(Point point, int cha, std::string name, const TCODColor& color)
                : Entity(point, cha, name, color)
    {
    }

    void Player::Update()
    {
    }

    // Derived Enemy class
    NPC::NPC(Point point, int cha, std::string name, const TCODColor& color)
                : Entity(point, cha, name, color)
    {
    }

    void NPC::Update()
    {
        if(EntityAI)
        {
            EntityAI->Update(this);
        }
    }
}