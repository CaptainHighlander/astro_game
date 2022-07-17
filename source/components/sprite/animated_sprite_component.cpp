#include "animated_sprite_component.hh"
namespace ns = components::sprite;


#pragma region Constructors, destructor and operators
ns::AnimatedSpriteComponent::AnimatedSpriteComponent(game_objects::sp_game_object_t&& owner, const ns::draw_order_t draw_oder, const float _anim_fps) :
    ns::SpriteComponent(std::move(owner), draw_oder), anim_fps(_anim_fps)
{
}

ns::AnimatedSpriteComponent::~AnimatedSpriteComponent(void)
{
}
#pragma endregion


#pragma region Public static methods
ns::sp_animated_sprite_t ns::AnimatedSpriteComponent::create(game_objects::sp_game_object_t owner, const ns::draw_order_t draw_oder, const float anim_fps)
{
	ns::sp_animated_sprite_t asc{ 
		new ns::AnimatedSpriteComponent { std::move(owner), draw_oder, anim_fps} 
	};
	return asc;
}
#pragma endregion


#pragma region Public overridden methods
void ns::AnimatedSpriteComponent::update(const float delta_time)
{
	this->ns::SpriteComponent::update(delta_time);

	if (this->anim_textures.empty() == false)
	{
		// Update the current frame based on frame rate and delta time
		this->current_frame += this->anim_fps * delta_time;
		
		// Wrap current frame if needed
		while (this->current_frame >= this->anim_textures.size())
		{
			this->current_frame -= this->anim_textures.size();
		}

		// Set the current texture
		this->ns::SpriteComponent::set_texture(this->anim_textures[static_cast<size_t>(this->current_frame)]);
	}
}
#pragma endregion


#pragma region Public methods:
float ns::AnimatedSpriteComponent::get_anim_fps(void) const noexcept
{
    return this->anim_fps;
}

void ns::AnimatedSpriteComponent::set_anim_fps(float _anim_fps)
{
    this->anim_fps = _anim_fps;
}

// Set the textures usd for animation
void ns::AnimatedSpriteComponent::set_animation_textures(std::vector<textures::sp_texture_t> textures)
{
    this->anim_textures = std::move(textures);
    this->current_frame = 0.0f;
    if (this->anim_textures.empty() == false)
    {
        // Set the active texture to first frame
        this->SpriteComponent::set_texture(this->anim_textures[0]);
    }
}
#pragma endregion
