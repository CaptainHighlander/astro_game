#include "texture.hh"
namespace ns = textures;


#include <textures/texture_manager.hh>


#pragma region Constuctors, destructor and operators
ns::Texture::Texture(SDL_Texture* _sld_texture, std::string_view _texture_name):
    sld_texture(_sld_texture), texture_name(std::move(_texture_name))
{
    if (this->sld_texture != nullptr)
    {
        // Get width/height of texture
        SDL_QueryTexture(this->sld_texture, nullptr, nullptr, reinterpret_cast<int*>(&this->width), reinterpret_cast<int*>(&this->height));
    }
}

ns::Texture::~Texture(void)
{
    if (this->sld_texture != nullptr)
        ns::TextureManager::remove_texture(this->texture_name.data());
}
#pragma endregion


#pragma region Public methods
ns::height_t ns::Texture::get_height(void) const noexcept
{
    return this->height;
}

const SDL_Texture& ns::Texture::get_sdl_texture_cref(void) const noexcept
{
    return (*this->sld_texture);
}

ns::width_t ns::Texture::get_width(void) const noexcept
{
    return this->width;
}
#pragma endregion
