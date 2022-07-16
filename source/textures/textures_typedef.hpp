#pragma once


#include <memory>


namespace textures
{
    class Texture;
    class TextureManager;

    typedef std::shared_ptr<Texture> sp_texture_t;
    typedef std::weak_ptr<Texture> wp_texture_t;
}
