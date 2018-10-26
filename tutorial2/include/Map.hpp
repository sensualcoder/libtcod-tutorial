#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

namespace tcodtutorial
{
    struct Tile
    {
        Tile() : CanWalk(true) {}

        bool CanWalk;
    };

    class Map
    {
        public:
            Map(int width, int height);

            bool IsWall(int posX, int posY) const;
            void SetWall(int posX, int posY);

            void Render() const;

        private:
            int Width, Height;
            std::vector<Tile> Tiles;
    };
}

#endif
