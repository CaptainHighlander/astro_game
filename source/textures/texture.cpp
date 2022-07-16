#include "texture.hh"
using namespace textures;


#include <textures/texture_manager.hh>


#pragma region Constuctors, destructor and operators
Texture::Texture(SDL_Texture* _sld_texture, std::string_view _texture_name):
    sld_texture(_sld_texture), texture_name(std::move(_texture_name))
{
}

Texture::~Texture(void)
{
    if (this->sld_texture != nullptr)
        TextureManager::remove_texture(this->texture_name.data());
}
#pragma endregion
