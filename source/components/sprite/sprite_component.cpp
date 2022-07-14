#include "sprite_component.hh"
using namespace components::sprite;


#include <game_objects/game_object.hh>
#include <math_plus/math.hpp>


#pragma region Constructors, destructor and operators
SpriteComponent::SpriteComponent(game_objects::wp_game_object_t&& owner, const components::sprite::sprite_draw_order_t _draw_order) :
    Component(std::move(owner)), draw_order(_draw_order)
{
}

SpriteComponent::~SpriteComponent(void)
{
}
#pragma endregion


#pragma region Public methods
void SpriteComponent::draw(SDL_Renderer* renderer)
{
    if (this->texture != nullptr)
    {
        SDL_Rect rect;

        // Scale the width/height by owner scale
        const auto owner_scale = this->owner.lock()->get_scale();
        rect.w = static_cast<int>(this->width * owner_scale);
        rect.h = static_cast<int>(this->height * owner_scale);

        // Center the rectangle around the position of the owner
        const auto owner_position = this->owner.lock()->get_position();
        rect.x = static_cast<int>(owner_position.x - (rect.w >> 1));
        rect.y = static_cast<int>(owner_position.y - (rect.h >> 1));

        // Draw
        SDL_RenderCopyEx(
            renderer,  // Render target to draw
            nullptr,  // Texture to draw
            nullptr,  // Part of texture to draw (nullptr if whole)
            &rect,  // Rectangle to draw onto the target
            math_plus::to_degrees(this->owner.lock()->get_rotation(), true),  // Rotation angle (in degrees, clockwise)
            nullptr,  // Point to rotate about (nullptr for center)
            SDL_FLIP_NONE  // How to flip texture
        );
    }
}

void SpriteComponent::set_texture(SDL_Texture* _texture)
{
    this->texture = _texture;
    if (this->texture != nullptr)
    {
        // Get width/height of texture
        SDL_QueryTexture(this->texture, nullptr, nullptr, reinterpret_cast<int*>(&this->width), reinterpret_cast<int*>(&this->height));
    }
}

components::sprite::sprite_draw_order_t SpriteComponent::get_draw_order(void) const noexcept
{
    return this->draw_order;
}

components::sprite::sprite_height_t SpriteComponent::get_height(void) const noexcept
{
    return this->height;
}

components::sprite::sprite_width_t SpriteComponent::get_width(void) const noexcept
{
    return this->width;
}
#pragma endrgion
