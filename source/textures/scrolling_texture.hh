#pragma once


#include <textures/textures_typedef.hpp>
#include <vector2.hpp>


namespace textures
{
    // Struct to encapsulate each scrolling image and its offset
    struct ScrollingTexture
    {
    public:  // Public attributes
        textures::sp_texture_t texture;
        Vector2 offset;
    public:  // Public constructors, destructor and operators
        ScrollingTexture(void);
        ScrollingTexture(const ScrollingTexture& other);
        ScrollingTexture(ScrollingTexture&& other) noexcept;
        ~ScrollingTexture(void);

        ScrollingTexture& operator=(ScrollingTexture other);

    private:  // Private static methods
        static void swap(ScrollingTexture& st1, ScrollingTexture& st2);
    };
}   