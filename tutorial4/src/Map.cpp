#include "Map.hpp"

#include <libtcod/libtcod.hpp>

namespace tcodtutorial
{
    static const int ROOM_MAX_SIZE = 12;
    static const int ROOM_MIN_SIZE = 6;

    static const TCODColor DarkWall(0, 0, 100);
    static const TCODColor DarkGround(50, 50, 150);

    class BspListener : public ITCODBspCallback 
    {
        public:
            BspListener(Map& map) : GameMap(map), RoomNum(0) {}
            
            bool visitNode(TCODBsp* node, void* userData) 
            {
                if(node->isLeaf() ) 
                {    
                    int x, y, w, h;
                    
                    // dig a room
                    TCODRandom* rng = TCODRandom::getInstance();
                    
                    w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
                    h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
                    x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
                    y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
                    
                    this->GameMap.Dig(x, y, x + w - 1, y + h - 1);
                    
                    if(RoomNum > 0) 
                    {
                        // dig a corridor from last room
                        this->GameMap.Dig(this->LastX, this->LastY, x + w / 2, this->LastY);
                        this->GameMap.Dig(x + w / 2, this->LastY, x + w / 2, y + h / 2);
                    }
                    
                    this->LastX = x + w / 2;
                    this->LastY = y + h / 2;
                    ++RoomNum;
                    this->Rooms.push_back(Room { this->LastX, this->LastY } );
                }
                return true;
            }

            std::vector<Room>& GetRooms()
            {
                return this->Rooms;
            }

        private:
            Map& GameMap; // a map to dig
            int RoomNum; // room number
            int LastX, LastY; // center of the last room
            std::vector<Room> Rooms;
    };

    Map::Map(int width, int height) : Width(width), Height(height), Tiles(width*height, Tile() )
    {
        TCODBsp bsp(0, 0, width, height);
        bsp.splitRecursive(nullptr, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
        BspListener listener(*this);
        bsp.traverseInvertedLevelOrder(&listener, nullptr);

        this->Rooms = listener.GetRooms();
    }

    void Map::Dig(int x1, int y1, int x2, int y2) 
    {
        if(x2 < x1) 
        {
            int tmp = x2;
            x2 = x1;
            x1 = tmp;
        }

        if(y2 < y1)
        {
            int tmp = y2;
            y2 = y1;
            y1 = tmp;
        }

        for (int x = x1; x <= x2; ++x)
        {
            for (int y = y1; y <= y2; ++y)
            {
                this->Tiles[x + y * this->Width].CanWalk = true;
            }
        }
    }

    void Map::GenMap()
    {
        this->Tiles.clear();
        this->Tiles = std::vector<Tile>(this->Width * this->Height, Tile() );

        TCODBsp bsp(0, 0, this->Width, this->Height);
        bsp.splitRecursive(nullptr, 8, ROOM_MAX_SIZE,ROOM_MAX_SIZE, 1.5f, 1.5f);
        BspListener listener(*this);
        bsp.traverseInvertedLevelOrder(&listener, nullptr);

        this->Rooms = std::move(listener.GetRooms() );
    }

    bool Map::IsWall(int x, int y) const 
    {
        return !this->Tiles[x + y * this->Width].CanWalk;
    }

    const Room& Map::GetRoom(int index) const
    {
        return this->Rooms[index];
    }
    
    void Map::Render() const 
    {
        for (int x = 0; x < this->Width; x++)
        {
            for (int y = 0; y < this->Height; y++) 
            {
                TCODConsole::root->setCharBackground( x, y,
                    this->IsWall(x, y) ? DarkWall : DarkGround );
            }
        }
    }
}
