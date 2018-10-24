#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include "libtcod.hpp"

namespace tcodtutorial
{
    static const int ROOM_MAX_SIZE = 12;
    static const int ROOM_MIN_SIZE = 6;

    struct Tile
    {
        Tile() : CanWalk(false) {}

        bool CanWalk;
    };

    class BspListener : public ITCODBspCallback
    {
        public:
            BspListener() : RoomNum(0) {}

            bool visitNode(TCODBsp* node, void* userData) override
            {
                if(node->isLeaf() )
                {
                    int x, y, w, h;

                    std::unique_ptr<TCODRandom> rng = std::unique_ptr<TCODRandom>(TCODRandom::getInstance() );
                    w = rng->getInt(ROOM_MIN_SIZE, node->w-2);
                    h = rng->getInt(ROOM_MIN_SIZE, node->h-2);
                    x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
                    y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
                    //map.createRoom(this->RoomNum == 0, x, y, x + w - 1, y + h - 1);
                }

                return true;
            }

        private:
            int RoomNum;
            int LastX, LastY;
    };

    class Map
    {
        public:
            Map(int width, int height);

            bool IsWall(int posX, int posY) const;
            void SetWall(int posX, int posY);

            void Render() const;

        private:
            void Dig(int x1, int y1, int x2, int y2);
            void CreateRoom();

            int Width, Height;
            std::vector<Tile> Tiles;
    };
}

#endif
