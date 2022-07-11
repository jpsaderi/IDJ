#include "../include/TileMap.hpp"

vector<string> string_split(string line, string delimiter){
    vector <string> list;
    regex space("[^"+delimiter+"]+");

    auto line_begin = sregex_iterator(line.begin(), line.end(), space);
    auto line_end = sregex_iterator();

    for (sregex_iterator i = line_begin; i != line_end; i++){
        smatch match = *i;
        list.push_back(match.str());
    }

    return list;
}

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated){
    Load(file);
    this -> tileSet = tileSet;
}

void TileMap::Load(string file){
    fstream File;
    File.open(file, ios::in);

    string line;
    getline(File, line);

    vector<string> list_split;
    list_split = string_split(line, ",");

    mapWidth = stoi(list_split[0]);
    mapHeight = stoi(list_split[1]);
    mapDepth = stoi(list_split[2]);

    while(getline(File, line)){
        if(line != ""){
            list_split = string_split(line, ",");
            for(unsigned int i = 0; i < list_split.size(); i++){
                tileMatrix.push_back(stoi(list_split[i])-1);
            }
        }
    }
    File.close();
}

void TileMap::SetTileSet(TileSet* tileSet){
    this -> tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    return tileMatrix.at( x + (y*mapWidth) + (z*mapWidth*mapHeight));
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    for(int i = 0; i < mapWidth; i++){
        for(int j = 0; j < mapHeight; j++){
            int x = i * tileSet -> GetTileWidth()-cameraX;
            int y = j * tileSet -> GetTileHeight()-cameraY;
            tileSet -> RenderTile((At(i,j,layer)),x,y);
        }
    }
}

void TileMap::Render(){
    for(int i = 0; i < mapDepth; i++){
        RenderLayer(i, Camera::pos.x*(1+(i*0.50)) , Camera::pos.y*(1+(i*0.50)));
    }
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;   
}

bool TileMap::Is(string type){
    return type == "TileMap";
}

void TileMap::Update(float dt){

}