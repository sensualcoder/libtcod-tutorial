#ifndef TILE_HPP
#define TILE_HPP

#include <vector>

namespace tcodtutorial
{
    struct Tile
    {
        Tile() : CanWalk(true) {}

        bool CanWalk;
    };

    class TileList
    {
        public:
            TileList(int width, int height) : Width(width), Height(height) {}

            void push_back(Tile tile) 
            { 
                if(this->Tiles.size() < this->Width * this->Height)
                    this->Tiles.push_back(tile); 
            }

            Tile& operator[](size_t item) { return this->Tiles[item]; }
            const Tile& operator[](size_t item) const { return this->Tiles[item]; }

        private:
            int Width, Height;
            std::vector<Tile> Tiles;
    };
}

#endif
