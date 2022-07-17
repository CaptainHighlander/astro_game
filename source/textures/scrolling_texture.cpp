#include "scrolling_texture.hh"


#include <utility>


namespace textures
{
    #pragma region Constructors, destructor and operators:
    ScrollingTexture::ScrollingTexture::ScrollingTexture(void)
    {  
    }

    ScrollingTexture::ScrollingTexture(const ScrollingTexture& other):
        texture(other.texture), offset(other.offset)
    {
    }

    ScrollingTexture::ScrollingTexture(ScrollingTexture&& other) noexcept
    {
        swap(*this, other);
    }

    ScrollingTexture::~ScrollingTexture(void)
    {
    }

    ScrollingTexture& ScrollingTexture::operator=(ScrollingTexture other)
    {
        swap(*this, other);
        return *this;
    }
    #pragma endregion


    #pragma region Public static methods
    void ScrollingTexture::swap(ScrollingTexture& st1, ScrollingTexture& st2)
    {
        std::swap(st1.texture, st2.texture);
        std::swap(st1.offset, st2.offset);
    }
    #pragma endregion
}
