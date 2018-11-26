#include "Engine.hpp"

namespace tcodtutorial
{
    static const int MAX_ROOM_MONSTERS = 3;

    Engine::Engine() : map_(new Map(80, 45) ), state_(STARTUP), FovRadius(10)
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
        playerptr_->SetPos(firstRoom.center_);
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
                TCODColor::desaturatedGreen, new NpcAi() ) );   
        }
        else
        {
            monster = std::shared_ptr<NPC>(new NPC(point, 'T', "troll", 
                TCODColor::darkerGreen, new NpcAi() ) );
        }
        
        entitylist_.push_back(monster);
        monster->AddObserver(this);
    }

    void Engine::ClearEntities()
    {
        for(auto i : entitylist_)
        {
            i->Clear();
        }

        entitylist_.clear();
    }

    bool Engine::CanWalk(Point point) const
    {
        if(map_->IsWall(point) )
        {
            return false;
        }

        for(auto entity : entitylist_)
        {
            if(entity->GetPos() == point)
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
            case TCODK_HOME:
            {
                GenerateMap();
                state_ = STARTUP;
                break;
            }
            default:
                break;
        }

        if(dx != 0 || dy != 0)
        {
            Point point = playerptr_->GetPos();
            point.x_ += dx;
            point.y_ += dy;

            if(CanWalk(point) )
            {
                playerptr_->SetPos(point);
                state_ = NEW_TURN;
            }
        }
    }

    void Engine::Update()
    {
        if(state_ == STARTUP)
        {
            map_->ComputeFov(playerptr_->GetPos(), FovRadius);
        }

        state_ = IDLE;

        World world { entitylist_, *map_ };

        HandleInput();

        playerptr_->Update(world);

        if(state_ == NEW_TURN)
        {
            map_->ComputeFov(playerptr_->GetPos(), FovRadius);
            map_->SetExplored();
            
            for(auto entity : entitylist_)
            {
                if(entity != playerptr_
                    && map_->IsInFov(entity->GetPos() ) )
                {
                    entity->Update(world);
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
            if(map_->IsInFov(entity->GetPos() ) )
            {
                entity->Render();
            }
        }
    }
}