#include "sprite_component.hh"
namespace ns = components::sprite;


#include <game_objects/game_object.hh>

#include <math_plus/math.hpp>

#include <textures/texture.hh>


#pragma region Constructors, destructor and operators
ns::SpriteComponent::SpriteComponent(game_objects::wp_game_object_t&& owner, const ns::draw_order_t _draw_order) :
    components::Component(std::move(owner)), draw_order(_draw_order)
{
}

ns::SpriteComponent::~SpriteComponent(void)
{
}

bool ns::SpriteComponent::operator<(const ns::SpriteComponent& other) const noexcept
{
    return this->draw_order < other.draw_order;
}

bool ns::SpriteComponent::operator>(const ns::SpriteComponent& other) const noexcept
{
    return this->draw_order > other.draw_order;
}
#pragma endregion


#pragma region Public methods
void ns::SpriteComponent::draw(SDL_Renderer& renderer)
{
    if (this->texture != nullptr)
    {
        SDL_Rect rect;

        // Scale the width/height by owner scale
        const auto owner_scale = this->owner.lock()->get_scale();
        rect.w = static_cast<int>(this->get_width() * owner_scale);
        rect.h = static_cast<int>(this->get_height() * owner_scale);

        // Center the rectangle around the position of the owner
        const auto owner_position = this->owner.lock()->get_position();
        rect.x = static_cast<int>(owner_position.x - (rect.w >> 1));
        rect.y = static_cast<int>(owner_position.y - (rect.h >> 1));

        const auto& sdl_texture = this->texture->get_sdl_texture_cref(); 

        // Draw
        SDL_RenderCopyEx(
            &renderer,  // Render target to draw
            &const_cast<SDL_Texture&>(sdl_texture),  // Texture to draw
            nullptr,  // Part of texture to draw (nullptr if whole)
            &rect,  // Rectangle to draw onto the target
            math_plus::to_degrees(this->owner.lock()->get_rotation(), true),  // Rotation angle (in degrees, clockwise)
            nullptr,  // Point to rotate about (nullptr for center)
            SDL_FLIP_NONE  // How to flip texture
        );
    }
}

void ns::SpriteComponent::set_texture(textures::sp_texture_t _texture)
{
    this->texture = std::move(_texture);
}

ns::draw_order_t ns::SpriteComponent::get_draw_order(void) const noexcept
{
    return this->draw_order;
}

ns::height_t ns::SpriteComponent::get_height(void) const noexcept
{
    return (this->texture) ?this->texture->get_height() : 0;
}

ns::width_t ns::SpriteComponent::get_width(void) const noexcept
{
    return (this->texture) ?this->texture->get_width() : 0;
}
#pragma endrgion
