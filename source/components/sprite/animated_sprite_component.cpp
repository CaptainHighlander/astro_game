#include "animated_sprite_component.hh"
using namespace components::sprite;


#pragma region Constructors, destructor and operators
AnimatedSpriteComponent::AnimatedSpriteComponent(game_objects::sp_game_object_t&& owner, const components::sprite::sprite_draw_order_t draw_oder, const float _anim_fps) :
    SpriteComponent(std::move(owner), draw_oder), anim_fps(_anim_fps)
{
}

AnimatedSpriteComponent::~AnimatedSpriteComponent(void)
{
}
#pragma endregion


#pragma region Public static methods
components::sprite::sp_animated_sprite_t AnimatedSpriteComponent::create(game_objects::sp_game_object_t owner, const components::sprite::sprite_draw_order_t draw_oder, const float anim_fps)
{
	components::sprite::sp_animated_sprite_t asc{ new AnimatedSpriteComponent { 
		std::move(owner), draw_oder, anim_fps
	} };
	return asc;
}
#pragma endregion


#pragma region Public overridden methods
void AnimatedSpriteComponent::update(const float delta_time)
{
	this->SpriteComponent::update(delta_time);

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
		this->SpriteComponent::set_texture(this->anim_textures[static_cast<size_t>(this->current_frame)]);
	}
}
#pragma endregion


#pragma region Public methods:
float AnimatedSpriteComponent::get_anim_fps(void) const noexcept
{
    return this->anim_fps;
}

void AnimatedSpriteComponent::set_anim_fps(float _anim_fps)
{
    this->anim_fps = _anim_fps;
}

// Set the textures usd for animation
void AnimatedSpriteComponent::set_animation_textures(std::vector<SDL_Texture*>&& textures)
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
