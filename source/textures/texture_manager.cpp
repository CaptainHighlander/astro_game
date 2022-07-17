#include "texture_manager.hh"
namespace ns = textures;


#include <engine.hh>
#include <textures/texture.hh>


#include <SDL2/SDL_image.h>


#pragma region Public static attributes initialization
std::unique_ptr<ns::TextureManager> ns::TextureManager::sprite_manager;
#pragma endregion


#pragma region Constructors and detructor:
ns::TextureManager::TextureManager(std::shared_ptr<Engine>&& _engine) :
    engine(std::move(_engine))
{
}

ns::TextureManager::~TextureManager(void)
{
}
#pragma endregion


#pragma region Public static methods
bool ns::TextureManager::init(std::shared_ptr<Engine> engine)
{
    bool result = false;
    if (!ns::TextureManager::sprite_manager)
    {
        ns::TextureManager::sprite_manager = std::unique_ptr<ns::TextureManager>{
            new ns::TextureManager{ std::move(engine) } 
        };
        result = true;
    }
    return result;
}

ns::sp_texture_t ns::TextureManager::load_texture(const std::string& file_name)
{
    return ns::TextureManager::sprite_manager->load_texture_int(file_name);
}

ns::sp_texture_t ns::TextureManager::load_texture(std::string&& file_name)
{
    return ns::TextureManager::load_texture(file_name);
}
#pragma endregion


#pragma region Private static methods
void ns::TextureManager::remove_texture(const std::string& file_name)
{
    ns::TextureManager::sprite_manager->remove_texture_int(file_name);
}
#pragma endregion


#pragma region Private methods:
ns::sp_texture_t ns::TextureManager::load_texture_int(const std::string& file_name)
{
    ns::sp_texture_t texture;

    SDL_Texture* sld_texture = nullptr;
    std::string_view key_texture;

    auto texture_it = this->textures_map.find(file_name);
    const bool is_texture_into_map = texture_it != this->textures_map.end();
    if (is_texture_into_map)
    {
        auto& texture_info = texture_it->second;
        key_texture = texture_it->first;
        sld_texture = texture_info.second;
        texture_info.first += 1;
    }
    else
    {
        // Load an image from a file
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (surface != nullptr)
        {
            // Create sld_texture from surface
            sld_texture = SDL_CreateTextureFromSurface(this->engine->get_sdl_renderer_ptr(), surface);
            SDL_FreeSurface(surface);
            if (sld_texture != nullptr)
            {
                auto inserted_el = this->textures_map.insert({ file_name, { 1, sld_texture } }).first;
                key_texture = inserted_el->first;                
            }
            else
            {
                SDL_Log("Failed to convert surface to sld_texture for %s", file_name.c_str());   
            }
        }
        else  // if surface == nullptr
            SDL_Log("Failed to load sld_texture file %s", file_name.c_str());
    }

    if (sld_texture != nullptr)
    {
        texture = ns::sp_texture_t{ new ns::Texture { sld_texture, key_texture } };
    }

    return texture;
}

void ns::TextureManager::remove_texture_int(const std::string& file_name)
{
    auto& texture_info = this->textures_map.at(file_name);
    auto& count = texture_info.first;
    count -= 1;
    if (count == 0)
    {
        SDL_DestroyTexture(texture_info.second);
        texture_info.second = nullptr;
        this->textures_map.erase(file_name);
    }
}
#pragma endregion
