#include "Engine.hpp"

#include <cstdio>

namespace tcodtutorial
{
    static const int MAX_ROOM_MONSTERS = 3;

    Engine::Engine() : GameMap(new Map(80, 45) ), State(GameState::STARTUP), FovRadius(10)
    {
        TCODConsole::initRoot(80, 50, "libtcod C++ tutorial 5");

        Room firstRoom = this->GameMap->GetRooms()[0];
        this->Player = std::make_unique<Actor>(firstRoom.PosX, firstRoom.PosY, 
            '@', "player", TCODColor::white);
        this->Actors.push(this->Player.get() );

        this->GenerateMonsters();
    }

    void Engine::GenerateMap()
    {
        this->Actors.clear();

        this->GameMap->GenerateMap();
        
        Room firstRoom = this->GameMap->GetRooms()[0];
        this->Player->SetPos(firstRoom.PosX, firstRoom.PosY);
        this->Actors.push(this->Player.get() );

        this->GenerateMonsters();
    }

    void Engine::GenerateMonsters()
    {
        TCODRandom* rng = TCODRandom::getInstance();

        for(auto room = this->GameMap->GetRooms().begin() + 1;
            room != this->GameMap->GetRooms().end(); ++room)
        {
            int numMonsters = rng->getInt(0, MAX_ROOM_MONSTERS);
            for( ; numMonsters > 0; --numMonsters)
            {
                int x = rng->getInt(room->X1, room->X2);
                int y = rng->getInt(room->Y1, room->Y2);

                if(this->CanWalk(x, y) )
                {
                    this->AddMonster(x, y);
                }
            }
        }
    }

    void Engine::AddMonster(int x, int y)
    {
        TCODRandom* rng = TCODRandom::getInstance();

        if(rng->getInt(0, 100) < 80)
        {
            this->Actors.push(new Enemy(x, y, 'o', "orc", 
                TCODColor::desaturatedGreen) );
        }
        else
        {
            this->Actors.push(new Enemy(x, y, 'T', "troll", 
                TCODColor::darkerGreen) );
        }
    }

    bool Engine::MoveOrAttack(int x, int y)
    {
        if(this->GameMap->IsWall(x, y) )
        {
            return false;
        }

        for(auto it = this->Actors.begin() + 1; it != this->Actors.end(); ++it)
        {
            auto actor = *it;

            if(actor->GetX() == x && actor->GetY() == y)
            {
                printf("The %s laughs at your puny attempts to attack him!\n", actor->GetName().c_str() );

                return false;
            }
        }

        this->Player->SetPos(x, y);

        return true;
    }

    bool Engine::CanWalk(int x, int y) const
    {
        if(this->GameMap->IsWall(x, y) )
        {
            return false;
        }

        for(auto actor : this->Actors)
        {
            if(actor->GetX() == x && actor->GetY() == y)
            {
                return false;
            }
        }

        return true;
    }

    void Engine::Update()
    {
        TCOD_key_t key;

        if(this->State == GameState::STARTUP)
        {
            this->GameMap->ComputeFov(this->Player->GetX(), this->Player->GetY(), this->FovRadius);
        }

        this->State = GameState::IDLE;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);

        int dx = 0,
            dy = 0;
        
        switch(key.vk) 
        {
            case TCODK_UP: 
            {
                --dy;
                break;
            }
            case TCODK_DOWN: 
            {
                ++dy;
                break;
            }
            case TCODK_LEFT: 
            {
                --dx;
                break;
            }
            case TCODK_RIGHT: 
            {
                ++dx;
                break;
            }
            case TCODK_ENTER:
            {
                this->GenerateMap();
                break;
            }
            default:
                break;
        }

        if(dx != 0 || dy != 0)
        {
            this->State = NEW_TURN;

            if(this->MoveOrAttack(this->Player->GetX() + dx, this->Player->GetY() + dy) )
            {
                this->GameMap->ComputeFov(this->Player->GetX(), this->Player->GetY(), this->FovRadius);
            }
        }

        if(this->State == NEW_TURN)
        {
            for(auto actor : this->Actors)
            {
                if(actor != this->Player.get() 
                    && this->GameMap->IsInFov(actor->GetX(), actor->GetY() ) )
                {
                    actor->Update();
                }
            }
        }
    }
    
    void Engine::Render() const
    {
        TCODConsole::root->clear();

        this->GameMap->Render();

        for(auto actor : this->Actors)
        {
            if(this->GameMap->IsInFov(actor->GetX(), actor->GetY() ) )
            {
                actor->Render();
            }
        }
    }
}