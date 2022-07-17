#include "texture.hh"
using namespace textures;


#include <textures/texture_manager.hh>


#pragma region Constuctors, destructor and operators
Texture::Texture(SDL_Texture* _sld_texture, std::string_view _texture_name):
    sld_texture(_sld_texture), texture_name(std::move(_texture_name))
{
    if (this->sld_texture != nullptr)
    {
        // Get width/height of texture
        SDL_QueryTexture(this->sld_texture, nullptr, nullptr, reinterpret_cast<int*>(&this->width), reinterpret_cast<int*>(&this->height));
    }
}

Texture::~Texture(void)
{
    if (this->sld_texture != nullptr)
        TextureManager::remove_texture(this->texture_name.data());
}
#pragma endregion


#pragma region Public methods
textures::height_t Texture::get_height(void) const noexcept
{
    return this->height;
}

const SDL_Texture& Texture::get_sdl_texture_cref(void) const noexcept
{
    return (*this->sld_texture);
}

textures::width_t Texture::get_width(void) const noexcept
{
    return this->width;
}
#pragma endregion
