#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include <libtcod/libtcod.hpp>

namespace tcodtutorial
{
    struct Room
    {
        int X1, Y1, X2, Y2;
        int PosX, PosY; // center of room
    };

    struct Tile 
    {
        Tile() : IsExplored(false) {}

        bool IsExplored; // has the player seen this tile?
    };
    
    class Map 
    {
        public:
            Map(int width, int height);

            bool IsWall(int x, int y) const;
            bool IsInFov(int x, int y) const;
            bool IsExplored(int x, int y) const;
            
            const std::vector<Room>& GetRooms() const;
            
            void Render() const;

            void Dig(int x1, int y1, int x2, int y2);
            void Dig(Room room);
            void SetExplored();
            void ComputeFov(int x, int y, int radius);
            void GenerateMap();
            
        private:
            int Width, Height;
            std::vector<Tile> Tiles;
            std::vector<Room> Rooms;
            std::unique_ptr<TCODMap> TileMap;
    };
}

#endif
