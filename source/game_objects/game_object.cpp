#include "game_object.hh"
using namespace game_objects;

#include <algorithm>

#include <components/component.hh>
#include <environments/game.hh>


#pragma region Public static attributes initialization:
uint32_t GameObject::next_id = 1;
#pragma endregion


#pragma region Constructors and destructor:
GameObject::GameObject(const environments::Game& game) :
    game_cref(game), id( GameObject::next_id++)
{
}

GameObject::~GameObject(void)
{
}
#pragma endregion


#pragma region Public static methods:
sp_game_object_t GameObject::create(const environments::Game& game)
{
    sp_game_object_t game_object{ 
        new game_objects::GameObject{ game } 
    };
    return game_object;
}
#pragma region endregion


#pragma region Public methods:
Vector2 GameObject::get_position(void) const noexcept
{
    return this->position;
}

float GameObject::get_rotation(void) const noexcept
{
    return this->rotation;
}

float GameObject::get_scale(void) const noexcept
{
    return this->scale;
}

GameObject::State GameObject::get_state(void) const noexcept
{
    return this->state;
}

bool GameObject::is_dead(void) const noexcept
{
    return this->state == GameObject::State::E_DEAD;
}

bool GameObject::is_to_erase(void) const noexcept
{
    return this->state == GameObject::State::E_TO_ERASE;
}

void GameObject::update_actor(const float delta_time)
{
    // Nothing to do
}

void GameObject::update(const float delta_time)
{
    if (this->state == State::E_ACTIVE)
    {
        this->update_components(delta_time);
        this->update_actor(delta_time);
    }
}

void GameObject::update_components(const float delta_time)
{
    for (auto const& component : this->components)
        component->update(delta_time);
}

void GameObject::add_component(components::sp_component_t component_to_add)
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

void GameObject::remove_component(const components::sp_component_t& component)
{
    auto iter = std::find(this->components.begin(), this->components.end(), component);
	if (iter != this->components.end())
	{
		this->components.erase(iter);
	}
}
#pragma endregion
