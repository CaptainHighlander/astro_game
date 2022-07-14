#include "sprite_manager.hh"
using namespace components::sprite;


#include <engine.hh>

#include <SDL2/SDL_image.h>


#include <cassert>


#pragma region Public static attributes initialization
std::unique_ptr<components::sprite::SpriteManager> SpriteManager::sprite_manager;
#pragma endregion


#pragma region Constructors and detructor:
SpriteManager::SpriteManager(std::shared_ptr<Engine>&& _engine) :
    engine(std::move(_engine))
{
}

SpriteManager::~SpriteManager(void)
{
}
#pragma endregion


#pragma region Public static methods
bool SpriteManager::init(std::shared_ptr<Engine> engine)
{
    bool result = false;
    if (!SpriteManager::sprite_manager)
    {
        SpriteManager::sprite_manager = std::unique_ptr<components::sprite::SpriteManager>{ new SpriteManager{ std::move(engine) } };
        result = true;
    }
    return result;
}

SDL_Texture* SpriteManager::load_texture(const std::string& file_name)
{
    return SpriteManager::sprite_manager->load_texture(file_name, true);
}

SDL_Texture* SpriteManager::load_texture(std::string&& file_name)
{
    return SpriteManager::load_texture(file_name);
}
#pragma endregion


#pragma region Private methods:
SDL_Texture* SpriteManager::load_texture(const std::string& file_name, const bool fake)
{
    assert(fake == true);

    SDL_Texture* texture = nullptr;

    if (fake && this->textures_map.contains(file_name) == true)
    {
        auto& el = this->textures_map.at(file_name);
        texture = el.second;
        el.first += 1;
    }
    else
    {
        // Load an image from a file
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (surface != nullptr)
        {
            // Create texture from surface
            texture = SDL_CreateTextureFromSurface(this->engine->get_sdl_renderer_ptr(), surface);
            SDL_FreeSurface(surface);
            if (texture != nullptr)
                this->textures_map.insert({file_name, { 1, texture } }); 
            else
                SDL_Log("Failed to convert surface to texture for %s", file_name.c_str());       
        }
        else  // if surface == nullptr
            SDL_Log("Failed to load texture file %s", file_name.c_str());
    }

    return texture;
}
#pragma endregion
