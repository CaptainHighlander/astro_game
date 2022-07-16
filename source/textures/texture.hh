#pragma once


#include <textures/textures_typedef.hpp>


#include <SDL2/SDL_render.h>

#include <string>
#include <string_view>
#include <unordered_map>


namespace textures
{
    class Texture
    {
        friend class textures::TextureManager;
    public:  // Public constructors, destructor and operators
        Texture(const Texture& other) = delete;
        ~Texture(void);

        Texture& operator=(const Texture& other) = delete;

    private:  // Private constructors
        Texture(SDL_Texture* sld_texture, std::string_view texture_name);

    private:  // Private attributes
        SDL_Texture* sld_texture = nullptr;
        std::string_view texture_name;
    };
}
