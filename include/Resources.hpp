#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

class Resources{
private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
    static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
    static unordered_map<string, shared_ptr<TTF_Font>> fontTable;
public:
    static shared_ptr<SDL_Texture> GetImage(string file);
    static shared_ptr<Mix_Music> GetMusic(string file);
    static shared_ptr<Mix_Chunk> GetSound(string file);
    static shared_ptr<TTF_Font> GetFont(string file, int fontSize);

    static void ClearImages();
    static void ClearMusics();
    static void ClearSounds();
    static void ClearFonts();
};

#endif