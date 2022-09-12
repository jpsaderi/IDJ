#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "SDL_include.h"
#include "GameObject.hpp"
#include "TileSet.hpp"
#include <string>
#include <vector>
#include <fstream>
#include "Camera.hpp"

class TileMap : public Component{
private:
    vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
public:
    TileMap(GameObject& associated, string file, TileSet* tileSet);
    void Load(string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z);
    void RenderLayer(int layer, int cameraX = 0, int CameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();
    
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif