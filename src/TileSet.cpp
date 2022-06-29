#include "../include/TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(*(new GameObject()), file){
    this -> tileWidth = tileWidth;
    this -> tileHeight = tileHeight;

    if(this -> tileSet.IsOpen() == true){
        this -> columns = this -> tileSet.GetWidth()/tileWidth;
        this -> rows = this -> tileSet.GetHeight()/tileHeight;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y){
    if(index <= unsigned((columns*rows)-1)){
        int clipx = (index%columns) * tileWidth;
        int clipy = (index/columns) * tileHeight;

        tileSet.SetClip(clipx, clipy, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}
int TileSet::GetTileHeight(){
    return tileHeight;
}