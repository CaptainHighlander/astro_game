#include "ship.hh"
namespace ns = game_objects;


#include <components/sprite/animated_sprite_component.hh>
#include <textures/texture_manager.hh>


#pragma region Constructors, destructor and operators:
ns::Ship::Ship(const environments::Game& game) :
    ns::GameObject(game)
{
}

ns::Ship::~Ship(void)
{
}
#pragma endregion


#pragma region Public static methods
ns::sp_ship_t ns::Ship::create(const environments::Game& game)
{
    ns::sp_ship_t new_ship{ new ns::Ship{ game } };
    auto asc = components::sprite::AnimatedSpriteComponent::create(new_ship->shared_from_this(), 100, 24);
    return new_ship;
}
#pragma endregion


#pragma region Public overridden methods
void ns::Ship::update_actor(const float delta_time)
{
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

void ns::Ship::process_keyboard(const uint8_t* state)
{
}
#pragma endregion
