#include "Engine.hpp"

namespace tcodtutorial
{
    static const int MAX_ROOM_MONSTERS = 3;

    Engine::Engine() : map_(new Map(80, 45) ), State(STARTUP), FovRadius(10)
    {
        TCODConsole::initRoot(80, 50, "libtcod C++ tutorial 6");

        Room firstRoom = map_->GetRooms()[0];
        playerptr_ = std::make_shared<Player>(firstRoom.center_, 
            '@', "player", TCODColor::white);
        playerptr_->AddObserver(this);

        entitylist_.push_back(playerptr_);

        GenerateMonsters();
    }

    void Engine::GenerateMap()
    {
        ClearEntities();

        map_->GenerateMap();
        
        Room firstRoom = map_->GetRooms()[0];

        playerptr_->AddObserver(this);
        playerptr_->SetPos(Point { firstRoom.center_.x_, firstRoom.center_.y_ } );
        entitylist_.push_back(playerptr_);

        GenerateMonsters();
    }

    void Engine::GenerateMonsters()
    {
        TCODRandom* rng = TCODRandom::getInstance();

        for(auto room = map_->GetRooms().begin() + 1;
            room != map_->GetRooms().end(); ++room)
        {
            int numMonsters = rng->getInt(0, MAX_ROOM_MONSTERS);
            for( ; numMonsters > 0; --numMonsters)
            {
                Point point
                { 
                    rng->getInt(room->topleft_.x_, room->bottomright_.x_),
                    rng->getInt(room->topleft_.y_, room->bottomright_.y_)
                };

                if(CanWalk(point) )
                {
                    AddMonster(point);
                }
            }
        }
    }

    void Engine::AddMonster(Point point)
    {
        TCODRandom* rng = TCODRandom::getInstance();

        std::shared_ptr<Entity> monster;

        if(rng->getInt(0, 100) < 80)
        {
            monster = std::shared_ptr<NPC>(new NPC(point, 'o', "orc", 
                TCODColor::desaturatedGreen) );
            entitylist_.push_back(monster);
        }
        else
        {
            monster = std::shared_ptr<NPC>(new NPC(point, 'T', "troll", 
                TCODColor::darkerGreen) );
            entitylist_.push_back(monster);
        }
        
        monster->AddObserver(this);
    }

    void Engine::ClearEntities()
    {
        for(auto i : entitylist_)
        {
            i->Clear();
        }
    }

    bool Engine::CanWalk(Point point) const
    {
        if(map_->IsWall(point) )
        {
            return false;
        }

        for(auto entity : entitylist_)
        {
            if(entity->GetX() == point.x_ && entity->GetY() == point.y_)
            {
                return false;
            }
        }

        return true;
    }

    // Implemented from Observer pure virtual method
    void Engine::OnNotify(const Entity& entity, Event event)
    {
    }

    void Engine::HandleInput()
    {
        TCOD_key_t key;

        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);

        int dx = 0,
            dy = 0;

        switch(key.vk)
        {
            case TCODK_UP:
                --dy;
                break;
            case TCODK_DOWN:
                ++dy;
                break;
            case TCODK_LEFT:
                --dx;
                break;
            case TCODK_RIGHT:
                ++dx;
                break;
            default:
                break;
        }

        if(dx != 0 || dy != 0)
        {
            Point point 
            { 
                playerptr_->GetX() + dx,
                playerptr_->GetY() + dy
            };

            if(CanWalk(point) )
            {
                playerptr_->SetPos(point);
                State = NEW_TURN;
            }
        }
    }

    void Engine::Update()
    {
        if(State == STARTUP)
        {
            map_->ComputeFov(Point { playerptr_->GetX(), playerptr_->GetY() }, FovRadius);
        }

        State = IDLE;

        HandleInput();

        playerptr_->Update();

        if(State == NEW_TURN)
        {
            map_->ComputeFov(Point { playerptr_->GetX(), playerptr_->GetY() }, FovRadius);
            map_->SetExplored();
            
            for(auto entity : entitylist_)
            {
                if(entity != playerptr_
                    && map_->IsInFov(Point { entity->GetX(), entity->GetY() } ) )
                {
                    entity->Update();
                }
            }
        }
    }
    
    void Engine::Render() const
    {
        TCODConsole::root->clear();

        map_->Render();

        for(auto entity : entitylist_)
        {
            if(map_->IsInFov(Point { entity->GetX(), entity->GetY() } ) )
            {
                entity->Render();
            }
        }
    }
}