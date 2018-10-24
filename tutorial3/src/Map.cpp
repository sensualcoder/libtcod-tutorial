#include "Map.hpp"

namespace tcodtutorial
{
    static const TCODColor DarkWall(0, 0, 100);
    static const TCODColor DarkGround(50, 50, 150);

    Map::Map(int width, int height) : Width(width), Height(height)
    {
        for(size_t i = 0; i < width*height; ++i)
        {
            this->Tiles.push_back(Tile() );
        }

        TCODBsp bsp(0, 0, width, height);
        bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
        BspListener listener;
        bsp.traverseInvertedLevelOrder(&listener, NULL);
    }

    bool Map::IsWall(int posX, int posY) const
    {
        return !Tiles[posX + posY * this->Width].CanWalk;
    }
    
    void Map::SetWall(int posX, int posY)
    {
        Tiles[posX + posY * this->Width].CanWalk = false;
    }

    void Map::Render() const
    {
        for(size_t x = 0; x < this->Width; ++x)
        {
            for(size_t y = 0; y < this->Height; ++y)
            {
                TCODConsole::root->setCharBackground(x, y,
                    this->IsWall(x, y) ? DarkWall : DarkGround );
            }
        }
    }
}