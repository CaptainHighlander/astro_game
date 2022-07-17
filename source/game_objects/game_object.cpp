#include "game_object.hh"
namespace ns = game_objects;


#include <components/sprite/sprite_component.hh>
#include <environments/game.hh>

#include <algorithm>


#pragma region Public static attributes initialization:
game_objects::unique_id_t ns::GameObject::next_id = 1;
#pragma endregion


#pragma region Constructors and destructor:
ns::GameObject::GameObject(const environments::Game& game, std::string_view _class_name) :
    game_cref(game), class_name(std::move(_class_name)),
    unique_id(ns::GameObject::next_id++)
{
}

ns::GameObject::~GameObject(void)
{
}
#pragma endregion


#pragma region Public methods:
void ns::GameObject::add_component(components::sp_component_t component_to_add)
{
    // Find the insertion point in the sorted vector
    const auto pos = std::find_if(
        this->components.begin(), this->components.end(), [&component_to_add](const auto& component) {
            return (*component) < (*component_to_add);
        }
    );

	// Inserts element before position of iterator
	this->components.insert(pos, std::move(component_to_add));
}

void ns::GameObject::draw(SDL_Renderer& renderer) const
{
    if (this->sprite)
    {
        this->sprite->draw(renderer);
    }
}

Vector2 ns::GameObject::get_position(void) const noexcept
{
    return this->position;
}

float ns::GameObject::get_rotation(void) const noexcept
{
    return this->rotation;
}

float ns::GameObject::get_scale(void) const noexcept
{
    return this->scale;
}

ns::GameObject::State ns::GameObject::get_state(void) const noexcept
{
    return this->state;
}

void ns::GameObject::handle_keyboard_inputs(const uint8_t* keyboard_state)
{
    // Nothing to do
}

bool ns::GameObject::is_dead(void) const noexcept
{
    return this->state == ns::GameObject::State::E_DEAD;
}

bool ns::GameObject::is_to_erase(void) const noexcept
{
    return this->state == ns::GameObject::State::E_TO_ERASE;
}

void ns::GameObject::remove_component(const components::sp_component_t& component)
{
    auto iter = std::find(this->components.begin(), this->components.end(), component);
	if (iter != this->components.end())
	{
		this->components.erase(iter);
	}
}

void ns::GameObject::set_position(const float x, const float y)
{
    if (x >= 0.0f && y >= 0.0f)
    {
        this->position.x = x;
        this->position.y = y;
    }
}

void ns::GameObject::set_scale(const float _scale)
{
    if (_scale > 0.0f)
    {
        this->scale = _scale;
    }
}

void ns::GameObject::update(const float delta_time)
{
    if (this->state == ns::GameObject::State::E_ACTIVE)
    {
        this->update_components(delta_time);
        this->update_game_object(delta_time);
    }
}
#pragma endregion


#pragma region Protected methods
void ns::GameObject::update_components(const float delta_time)
{
    for (auto const& component : this->components)
        component->update(delta_time);
}

void ns::GameObject::update_game_object(const float delta_time)
{
    // Nothing to do
}
#pragma endregion
