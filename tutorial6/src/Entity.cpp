#include "Entity.hpp"

namespace tcodtutorial
{
    Entity::Entity(Point position, int displaycharacter, std::string name, const TCODColor& color) 
        : position_(position), displaycharacter_(displaycharacter), name_(name), color_(color), isblocker_(true),
          ai_(nullptr), attacker_(nullptr), destructible_(nullptr)
    {
    }

    void Entity::Render() const
    {
        TCODConsole::root->setChar(position_.x_, position_.y_, displaycharacter_);
        TCODConsole::root->setCharForeground(position_.x_, position_.y_, color_);
    }

    Point Entity::GetPos() const
    {
        return position_;
    }

    std::string Entity::GetName() const
    {
        return name_;
    }

    void Entity::SetPos(Point point)
    {
        position_ = point;
    }

    void Entity::SetAI(AiComponent* ai)
    {
        ai == nullptr 
            ? ai_ = nullptr
            : ai_ = std::unique_ptr<AiComponent>(ai);
    }

    void Entity::SetAttacker(AttackerComponent* attacker)
    {
        attacker == nullptr 
            ? attacker_ = nullptr
            : attacker_ = std::unique_ptr<AttackerComponent>(attacker);
    }
    
    void Entity::SetDestructible(DestructibleComponent* destructible)
    {
        destructible == nullptr
            ? destructible_ = nullptr
            : destructible_ = std::unique_ptr<DestructibleComponent>(destructible);
    }

    // Derived Player class
    Player::Player(Point point, int cha, std::string name, const TCODColor& color)
                : Entity(point, cha, name, color)
    {
    }

    void Player::Update(World& world)
    {
    }

    // Derived Enemy class
    NPC::NPC(Point point, int cha, std::string name, const TCODColor& color, AiComponent* ai)
                : Entity(point, cha, name, color)
    {
        SetAI(ai);
    }

    void NPC::Update(World& world)
    {
        ai_->Update(this, world);
    }
}