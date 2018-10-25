#ifndef MAP_HPP
#define MAP_HPP

#include "Tile.hpp"

namespace tcodtutorial
{
    class Map
    {
        public:
            Map(int width, int height);

            bool IsWall(int posX, int posY) const;
            void SetWall(int posX, int posY);

            void Render() const;

        private:
            int Width, Height;
            TileList Tiles;
    };
}

#endif
