#ifndef TILESET_HPP
#define TILESET_HPP

#include "SDL_include.h"
#include "Sprite.hpp"
#include <string>

class TileSet{
private:
    Sprite tileSet;
    GameObject* associated;
    int rows;
    int columns;

    int tileWidth;
    int tileHeight;
public:
    TileSet(int tileWidth, int tileHeight, string file);
    ~TileSet();	
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};

#endif