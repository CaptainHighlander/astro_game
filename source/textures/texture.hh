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

        // Constant reference to texture name
        std::string_view texture_name;

        // Width of texture
        textures::width_t width = 0;

        // Height of texture
        textures::height_t height = 0;
    
    public:  // Public methods

        [[nodiscard]] textures::height_t get_height(void) const noexcept;

        [[nodiscard]] const SDL_Texture& get_sdl_texture_cref(void) const noexcept;

        [[nodiscard]] textures::width_t get_width(void) const noexcept;
    };
}
