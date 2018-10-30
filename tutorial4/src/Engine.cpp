#include "Engine.hpp"

namespace tcodtutorial
{
    Engine::Engine() : FovRadius(10), ComputeFov(true)
    {
        TCODConsole::initRoot(80, 50, "libtcod C++ tutorial 4");

        this->GameMap = std::make_unique<Map>(80, 45);

        Room firstRoom = this->GameMap->GetRooms()[0];
        this->Player = std::make_unique<Actor>(firstRoom.PosX, firstRoom.PosY, '@', TCODColor::white);
        this->Actors.push(this->Player.get() );

        for(size_t i = 1; i < this->GameMap->GetRooms().size(); ++i)
        {
            Room room = this->GameMap->GetRooms()[i];
            this->Actors.push(new Actor(room.PosX, room.PosY, '@', TCODColor::white) );
        }
    }

    void Engine::GenerateMap()
    {
        this->Actors.clear();

        this->GameMap->GenerateMap();
        
        Room firstRoom = this->GameMap->GetRooms()[0];
        this->Player->SetPos(firstRoom.PosX, firstRoom.PosY);
        this->Actors.push(this->Player.get() );

        for(size_t i = 1; i < this->GameMap->GetRooms().size(); ++i)
        {
            Room room = this->GameMap->GetRooms()[i];
            this->Actors.push(new Actor(room.PosX, room.PosY, '@', TCODColor::white) );
        }
    }

    void Engine::Update()
    {
        TCOD_key_t key;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);
        
        switch(key.vk) 
        {
            case TCODK_UP: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX(), this->Player->GetY()-1) )
                {
                    this->Player->MoveUp();   
                    this->ComputeFov = true;
                }
                break;
            }
            case TCODK_DOWN: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX(), this->Player->GetY()+1) )
                {
                    this->Player->MoveDown();
                    this->ComputeFov = true;
                }
                break;
            }
            case TCODK_LEFT: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX()-1, this->Player->GetY() ) )
                {
                    this->Player->MoveLeft(); 
                    this->ComputeFov = true;
                }
                break;
            }
            case TCODK_RIGHT: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX()+1, this->Player->GetY() ) )
                {
                   this->Player->MoveRight(); 
                   this->ComputeFov = true;
                }
                break;
            }
            case TCODK_ENTER:
            {
                this->GenerateMap();

                this->ComputeFov = true;
                break;
            }
            default:
                break;
        }

        if(this->ComputeFov)
        {
            this->GameMap->ComputeFov(this->Player->GetX(), this->Player->GetY(), this->FovRadius);
            this->GameMap->SetExplored();

            this->ComputeFov = false;
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