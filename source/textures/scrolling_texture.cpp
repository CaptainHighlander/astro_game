#include "scrolling_texture.hh"
namespace ns = textures;

#include <utility>


#pragma region Constructors, destructor and operators:
ns::ScrollingTexture::ScrollingTexture::ScrollingTexture(void)
{  
}

ns::ScrollingTexture::ScrollingTexture(const ns::ScrollingTexture& other):
    texture(other.texture), offset(other.offset)
{
}

ns::ScrollingTexture::ScrollingTexture(ns::ScrollingTexture&& other) noexcept
{
    swap(*this, other);
}

ns::ScrollingTexture::~ScrollingTexture(void)
{
}

ns::ScrollingTexture& ns::ScrollingTexture::operator=(ns::ScrollingTexture other)
{
    swap(*this, other);
    return *this;
}
#pragma endregion


#pragma region Public static methods
void ns::ScrollingTexture::swap(ns::ScrollingTexture& st1, ns::ScrollingTexture& st2)
{
    std::swap(st1.texture, st2.texture);
    std::swap(st1.offset, st2.offset);
}
#pragma endregion
