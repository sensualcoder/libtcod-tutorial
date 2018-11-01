#include "Map.hpp"

namespace tcodtutorial
{
    static const int ROOM_MAX_SIZE = 12;
    static const int ROOM_MIN_SIZE = 6;

    static const TCODColor LightWall(130, 110, 50);
    static const TCODColor LightGround(200, 100, 50);
    static const TCODColor DarkWall(0, 0, 100);
    static const TCODColor DarkGround(50, 50, 150);

    class BspListener : public ITCODBspCallback 
    {
        public:
            BspListener(Map* map) : GameMap(map), RoomNum(0) {}
            
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
                    
                    Room room = Room { x, y, x + w - 1, y + h - 1, x + w / 2, y + h / 2 };
                    this->GameMap->Dig(room);
                    
                    if(RoomNum > 0) 
                    {
                        // dig a corridor from last room
                        this->GameMap->Dig(this->LastX, this->LastY, x + w / 2, this->LastY);
                        this->GameMap->Dig(x + w / 2, this->LastY, x + w / 2, y + h / 2);
                    }
                    
                    this->LastX = x + w / 2;
                    this->LastY = y + h / 2;
                    ++RoomNum;
                }
                return true;
            }

        private:
            Map* GameMap; // a map to dig
            int RoomNum; // room number
            int LastX, LastY; // center of the last room
    };

    Map::Map(int width, int height) 
        : Width(width), Height(height), Tiles(width*height, Tile() ), 
            TileMap(new TCODMap(width, height) )
    {
        TCODBsp bsp(0, 0, width, height);
        bsp.splitRecursive(nullptr, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
        BspListener listener(&(*this) );
        bsp.traverseInvertedLevelOrder(&listener, nullptr);
    }

    bool Map::IsWall(int x, int y) const 
    {
        return !this->TileMap->isWalkable(x, y);
    }

    bool Map::IsInFov(int x, int y) const
    {
        if(this->TileMap->isInFov(x, y) )
        {
            return true;
        }

        return false;
    }

    bool Map::IsExplored(int x, int y) const
    {
        return this->Tiles[x + y * this->Width].IsExplored;
    }

    const std::vector<Room>& Map::GetRooms() const
    {
        return this->Rooms;
    }
    
    void Map::Render() const 
    {
        for (int x = 0; x < this->Width; x++)
        {
            for (int y = 0; y < this->Height; y++) 
            {
                if(this->IsInFov(x, y) )
                {
                    TCODConsole::root->setCharBackground( x, y,
                        this->IsWall(x, y) ? LightWall : LightGround );
                }
                else if(this->IsExplored(x, y) )
                {
                    TCODConsole::root->setCharBackground( x, y,
                        this->IsWall(x, y) ? DarkWall : DarkGround );
                }
            }
        }
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
                this->TileMap->setProperties(x, y, true, true);
            }
        }
    }

    void Map::Dig(Room room)
    {
        this->Dig(room.X1, room.Y1, room.X2, room.Y2);
        this->Rooms.push_back(room);
    }

    void Map::SetExplored()
    {
        for (int x = 0; x < this->Width; x++)
        {
            for (int y = 0; y < this->Height; y++) 
            {
                if(this->IsInFov(x, y) )
                {
                    this->Tiles[x + y * this->Width].IsExplored = true;
                }
            }
        }
    }

    void Map::ComputeFov(int x, int y, int radius)
    {
        this->TileMap->computeFov(x, y, radius);
    }

    void Map::GenerateMap()
    {
        this->Tiles.clear();
        this->Tiles = std::vector<Tile>(this->Width * this->Height, Tile() );

        this->TileMap = std::make_unique<TCODMap>(this->Width, this->Height);

        this->Rooms.clear();

        TCODBsp bsp(0, 0, this->Width, this->Height);
        bsp.splitRecursive(nullptr, 8, ROOM_MAX_SIZE,ROOM_MAX_SIZE, 1.5f, 1.5f);
        BspListener listener(&(*this) );
        bsp.traverseInvertedLevelOrder(&listener, nullptr);
    }
}
