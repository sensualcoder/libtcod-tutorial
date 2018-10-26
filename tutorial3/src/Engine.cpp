#include "Engine.hpp"

namespace tcodtutorial
{
    Engine::Engine()
    {
        TCODConsole::initRoot(80, 50, "libtcod C++ tutorial 2");

        this->GameMap = std::make_unique<Map>(80, 45);

        Room firstRoom = this->GameMap->GetRoom(0);
        this->Player = std::make_unique<Actor>(firstRoom.PosX, firstRoom.PosY, '@', TCODColor::white);
        this->Actors.push(this->Player.get() );

        for(auto room = this->GameMap->GetRooms().begin() + 1; room != this->GameMap->GetRooms().end(); room++)
        {
            this->Actors.push(new Actor(room->PosX, room->PosY, '@', TCODColor::yellow) );
        }
    }

    void Engine::Update()
    {
        TCOD_key_t key;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        
        switch(key.vk) 
        {
            case TCODK_UP: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX(), this->Player->GetY() - 1) )
                {
                    this->Player->MoveUp();   
                }
                break;
            }
            case TCODK_DOWN: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX(), this->Player->GetY() + 1) )
                {
                    this->Player->MoveDown();
                }
                break;
            }
            case TCODK_LEFT: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX() - 1, this->Player->GetY() ) )
                {
                    this->Player->MoveLeft(); 
                }
                break;
            }
            case TCODK_RIGHT: 
            {
                if(!this->GameMap->IsWall(
                    this->Player->GetX() + 1, this->Player->GetY() ) )
                {
                   this->Player->MoveRight(); 
                }
                break;
            }
            case TCODK_ENTER:
            {
                this->GameMap->GenMap();

                Room firstRoom = this->GameMap->GetRoom(0);

                this->Actors.clear();
                this->Player->SetPos(firstRoom.PosX, firstRoom.PosY);

                this->Actors.push(this->Player.get() );

                for(auto room = this->GameMap->GetRooms().begin() + 1; room != this->GameMap->GetRooms().end(); room++)
                {
                    this->Actors.push(new Actor(room->PosX, room->PosY, '@', TCODColor::yellow) );
                }
                break;
            }
            default:
                break;
        }
    }
    
    void Engine::Render()
    {
        TCODConsole::root->clear();

        this->GameMap->Render();

        for(auto actor : this->Actors)
        {
            actor->Render();
        }
    }
}