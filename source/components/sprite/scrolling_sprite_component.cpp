#include "scrolling_sprite_component.hh"
namespace ns = components::sprite;

#include <game_objects/game_object.hh>
#include <textures/texture.hh>


#pragma region Constructors, destructor and operators
ns::ScrollingSpriteComponent::ScrollingSpriteComponent(game_objects::wp_game_object_t&& owner, const ns::draw_order_t _draw_order) :
    ns::SpriteComponent(std::move(owner), _draw_order)
{
}

ns::ScrollingSpriteComponent::~ScrollingSpriteComponent(void)
{
}
#pragma endregion


#pragma region Public static methods
ns::sp_scrolling_sprite_t ns::ScrollingSpriteComponent::create(game_objects::sp_game_object_t owner, const ns::draw_order_t draw_oder)
{
	ns::sp_scrolling_sprite_t bg{ 
		new ns::ScrollingSpriteComponent { std::move(owner), draw_oder} 
	};
	return bg;
}
#pragma endregion


#pragma region Public overridden methods:
void ns::ScrollingSpriteComponent::draw(SDL_Renderer& renderer)
{
    // Draw each background texture
    auto owner = this->owner.lock();
	for (auto& scrolling_texture : this->scrolling_textures)
	{
        if (scrolling_texture.texture)
        {
            SDL_Rect r;
            
            // Assume screen size dimensions
            r.w = static_cast<int>(this->screen_size.x);
            r.h = static_cast<int>(this->screen_size.y);

            // Center the rectangle around the position of the owner
            r.x = static_cast<int>(owner->get_position().x - r.w / 2 + scrolling_texture.offset.x);
            r.y = static_cast<int>(owner->get_position().y - r.h / 2 + scrolling_texture.offset.y);

            const auto& sdl_texture = scrolling_texture.texture->get_sdl_texture_cref();

            // Draw this background
            SDL_RenderCopy(&renderer, &const_cast<SDL_Texture&>(sdl_texture), nullptr, &r);
        }
	}
}

void ns::ScrollingSpriteComponent::update(const float delta_time)
{
    this->SpriteComponent::update(delta_time);

    for (auto& scrolling_texture : this->scrolling_textures)
    {
        // Update the x offset
        scrolling_texture.offset.x += this->scroll_speed * delta_time;
        // If this is completely off the screen, reset offet to the right of the last scrolling texture
        if (scrolling_texture.offset.x < -this->screen_size.x)
            scrolling_texture.offset.x = (this->scrolling_textures.size() - 1) * this->screen_size.x - 1;
    }
}
#pragma endregion


#pragma region Public methods
float ns::ScrollingSpriteComponent::get_scrool_speed(void) const noexcept
{
    return this->scroll_speed;
}

void ns::ScrollingSpriteComponent::set_screen_size(const Vector2& size)
{
    this->screen_size = size;
}

void ns::ScrollingSpriteComponent::set_scrool_speed(const float speed)
{
    this->scroll_speed = speed;
}

void ns::ScrollingSpriteComponent::set_textures(const std::vector<textures::sp_texture_t>& textures)
{
    // This cose assumes that each image has a width corresponding to the screen width, 
    // but i's certainly possible to modify the code to account for variable sizes
    uint32_t count = 0;
    for (auto tex : textures)
    {
        textures::ScrollingTexture temp;
        temp.texture = std::move(tex);
        // Each texture is screen width in offset
        temp.offset.x = count * this->screen_size.x;
        temp.offset.y = 0;
        this->scrolling_textures.push_back(std::move(temp));
        count += 1;
    }
}
#pragma endregion