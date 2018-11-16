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
            BspListener(Map* map) : map_(map), RoomNum(0) {}
            
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
                    
                    Room room = Room 
                    { 
                        { x, y }, 
                        { x + w - 1, y + h - 1 }, 
                        { x + w / 2, y + h / 2 } 
                    };
                    map_->Dig(room);
                    
                    if(RoomNum > 0) 
                    {
                        // dig a corridor from last room
                        map_->Dig(Point { LastX, LastY }, Point { x + w / 2, LastY } );
                        map_->Dig(Point { x + w / 2, LastY }, Point { x + w / 2, y + h / 2 } );
                    }
                    
                    LastX = x + w / 2;
                    LastY = y + h / 2;
                    ++RoomNum;
                }
                return true;
            }

        private:
            Map* map_; // a map to dig
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

    bool Map::IsWall(Point point) const 
    {
        return !TileMap->isWalkable(point.x_, point.y_);
    }

    bool Map::IsInFov(Point point) const
    {
        if(TileMap->isInFov(point.x_, point.y_) )
        {
            return true;
        }

        return false;
    }

    bool Map::IsExplored(Point point) const
    {
        return Tiles[point.x_ + point.y_ * Width].IsExplored;
    }

    const std::vector<Room>& Map::GetRooms() const
    {
        return Rooms;
    }
    
    void Map::Render() const 
    {
        for (int x = 0; x < Width; x++)
        {
            for (int y = 0; y < Height; y++) 
            {  
                Point point { x, y };

                if(IsInFov(point) )
                {
                    TCODConsole::root->setCharBackground( x, y,
                        IsWall(point) ? LightWall : LightGround );
                }
                else if(IsExplored(point) )
                {
                    TCODConsole::root->setCharBackground( x, y,
                        IsWall(point) ? DarkWall : DarkGround );
                }
            }
        }
    }

    void Map::Dig(Point point1, Point point2) 
    {
        if(point2.x_ < point1.x_) 
        {
            int tmp = point2.x_;
            point2.x_ = point1.x_;
            point1.x_ = tmp;
        }

        if(point2.y_ < point1.y_) 
        {
            int tmp = point2.y_;
            point2.y_ = point1.y_;
            point1.y_ = tmp;
        }

        for (int x = point1.x_; x <= point2.x_; ++x)
        {
            for (int y = point1.y_; y <= point2.y_; ++y)
            {
                TileMap->setProperties(x, y, true, true);
            }
        }
    }

    void Map::Dig(Room room)
    {
        Dig(room.topleft_, room.bottomright_);
        Rooms.push_back(room);
    }

    void Map::SetExplored()
    {
        for (int x = 0; x < Width; x++)
        {
            for (int y = 0; y < Height; y++) 
            {
                if(IsInFov(Point { x, y } ) )
                {
                    Tiles[x + y * Width].IsExplored = true;
                }
            }
        }
    }

    void Map::ComputeFov(Point point, int radius)
    {
        TileMap->computeFov(point.x_, point.y_, radius);
    }

    void Map::GenerateMap()
    {
        Tiles.clear();
        Tiles = std::vector<Tile>(Width * Height, Tile() );

        TileMap = std::make_unique<TCODMap>(Width, Height);

        Rooms.clear();

        TCODBsp bsp(0, 0, Width, Height);
        bsp.splitRecursive(nullptr, 8, ROOM_MAX_SIZE,ROOM_MAX_SIZE, 1.5f, 1.5f);
        BspListener listener(&(*this) );
        bsp.traverseInvertedLevelOrder(&listener, nullptr);
    }
}
