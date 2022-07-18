#include "animated_sprite_component.hh"
namespace ns = components::sprite;

#include <animations/animation.hh>


#pragma region Constructors, destructor and operators
ns::AnimatedSpriteComponent::AnimatedSpriteComponent(game_objects::sp_game_object_t&& owner, const ns::draw_order_t draw_oder) :
    ns::SpriteComponent(std::move(owner), draw_oder)
{
}

ns::AnimatedSpriteComponent::~AnimatedSpriteComponent(void)
{
}
#pragma endregion


#pragma region Public static methods
ns::sp_animated_sprite_t ns::AnimatedSpriteComponent::create(game_objects::sp_game_object_t owner, const ns::draw_order_t draw_oder)
{
	ns::sp_animated_sprite_t asc{ 
		new ns::AnimatedSpriteComponent{ std::move(owner), draw_oder } 
	};
	return asc;
}
#pragma endregion


#pragma region Public overridden methods
void ns::AnimatedSpriteComponent::update(const float delta_time)
{
	this->ns::SpriteComponent::update(delta_time);

	if (this->current_animation.empty() == false)
	{
		auto& animation_to_play = this->animations.at(current_animation);
		const auto current_frame = animation_to_play->play(delta_time);

		// Set the current texture
		this->ns::SpriteComponent::set_texture(animation_to_play->get_texture(static_cast<size_t>(current_frame)));
	}
}
#pragma endregion


#pragma region Public methods
void ns::AnimatedSpriteComponent::add_animation(animations::up_animation_t&& animation, const bool set_as_to_run)
{
	auto animation_name = animation->get_name_view();
	if (this->animations.contains(animation_name) == false)
	{
		this->animations.insert({ std::move(animation_name), std::move(animation) });
		if (set_as_to_run == true)
			this->set_current_animation(animation_name.data());
	}
}

void ns::AnimatedSpriteComponent::set_current_animation(std::string animation_name)
{
	auto anim_iterator = this->animations.find(animation_name);
	if (anim_iterator != this->animations.cend())
	{
		auto& animation = anim_iterator->second;

		// Set current animation
		this->current_animation = anim_iterator->first;

		// Restart animation
		animation->restart();

		// Set the active texture to first frame
        this->SpriteComponent::set_texture(animation->get_texture(0));
	}
}
#pragma endregion
