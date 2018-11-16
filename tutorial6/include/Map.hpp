#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include <libtcod/libtcod.hpp>

#include "Point.hpp"

namespace tcodtutorial
{
    struct Room
    {
        Point topleft_, bottomright_, center_;
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

            bool IsWall(Point point) const;
            bool IsInFov(Point point) const;
            bool IsExplored(Point point) const;
            
            const std::vector<Room>& GetRooms() const;
            
            void Render() const;

            void Dig(Point point1, Point point2);
            void Dig(Room room);
            void SetExplored();
            void ComputeFov(Point point, int radius);
            void GenerateMap();
            
        private:
            int Width, Height;
            std::vector<Tile> Tiles;
            std::vector<Room> Rooms;
            std::unique_ptr<TCODMap> TileMap;
    };
}

#endif
