#include "ship.hh"
namespace ns = game_objects;

#include <SDL2/SDL_keyboard.h>


#pragma region Constructors, destructor and operators:
ns::Ship::Ship(const environments::Game& game, std::string_view class_name) :
    ns::GameObject(game, std::move(class_name))
{
}

ns::Ship::~Ship(void)
{
}
#pragma endregion


#pragma region Public overridden methods
void ns::Ship::handle_keyboard_inputs(const uint8_t* keyboard_state)
{
    this->ns::GameObject::handle_keyboard_inputs(keyboard_state);

	this->right_speed = 0.0f;
	this->down_speed = 0.0f;
	// right/left
	if (keyboard_state[SDL_SCANCODE_D] == 1)
	{
		this->right_speed += 250.0f;
	}
	if (keyboard_state[SDL_SCANCODE_A] == 1)
	{
		this->right_speed -= 250.0f;
	}
	// up/down
	if (keyboard_state[SDL_SCANCODE_S] == 1)
	{
		this->down_speed += 300.0f;
	}
	if (keyboard_state[SDL_SCANCODE_W] == 1)
	{
		this->down_speed -= 300.0f;
	}
}

void ns::Ship::update_game_object(const float delta_time)
{
    this->ns::GameObject::update_game_object(delta_time);

    this->position.x += this->right_speed * delta_time;
    this->position.y += this->down_speed * delta_time;
    // Restrict position to left half of screen
	if (this->position.x < 25.0f)
	{
		this->position.x = 25.0f;
	}
	else if (this->position.x > 500.0f)
	{
		this->position.x = 500.0f;
	}
	if (this->position.y < 25.0f)
	{
		this->position.y = 25.0f;
	}
	else if (this->position.y > 743.0f)
	{
		this->position.y = 743.0f;
	}
}
#pragma endregion


#pragma region Public methods
ns::speed_t ns::Ship::get_down_speed(void) const noexcept
{
    return this->down_speed;
}
        
ns::speed_t ns::Ship::get_right_speed(void) const noexcept
{
    return this->right_speed;
}
#pragma endregion
