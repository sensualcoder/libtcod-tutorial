#include "Engine.hpp"

namespace tcodtutorial
{
    Engine::Engine()
    {
        TCODConsole::initRoot(80, 50, "libtcod C++ tutorial 2");

        this->Player = std::make_unique<Actor>(40, 25, '@', TCODColor::white);
        this->NPC = std::make_unique<Actor>(60, 13, '@', TCODColor::yellow);

        this->Actors.push(this->Player.get() );
        this->Actors.push(this->NPC.get() );

        this->GameMap = std::make_unique<Map>(80, 45);
    }

    void Engine::Update()
    {
        TCOD_key_t key;
        
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        
        switch(key.vk) 
        {
            case TCODK_UP: 
                if(!this->GameMap->IsWall(
                    this->Player->GetX(), this->Player->GetY()-1) )
                {
                    this->Player->MoveUp();   
                }
                break;
            case TCODK_DOWN: 
                if(!this->GameMap->IsWall(
                    this->Player->GetX(), this->Player->GetY()+1) )
                {
                    this->Player->MoveDown();
                }
                break;
            case TCODK_LEFT: 
                if(!this->GameMap->IsWall(
                    this->Player->GetX()-1, this->Player->GetY() ) )
                {
                    this->Player->MoveLeft(); 
                }
                break;
            case TCODK_RIGHT: 
                if(!this->GameMap->IsWall(
                    this->Player->GetX()+1, this->Player->GetY() ) )
                {
                   this->Player->MoveRight(); 
                }
                break;
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