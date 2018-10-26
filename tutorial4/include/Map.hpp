#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

namespace tcodtutorial
{
    struct Room
    {
        int PosX, PosY; // center of room
    };

    struct Tile 
    {
        Tile() : CanWalk(false) {}

        bool CanWalk; // can we walk through this tile?
    };
    
    class Map 
    {
        public:
            Map(int width, int height);

            bool IsWall(int x, int y) const;
            const Room& GetRoom(int index) const;
            
            void Render() const;

            void Dig(int x1, int y1, int x2, int y2);
            void GenMap();
            
        private:
            int Width, Height;
            std::vector<Tile> Tiles;
            std::vector<Room> Rooms;
    };
}

#endif
