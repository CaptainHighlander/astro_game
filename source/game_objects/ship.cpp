#include "ship.hh"
using namespace game_objects;


#include <components/sprite/animated_sprite_component.hh>
#include <textures/texture_manager.hh>


#pragma region Constructors, destructor and operators:
Ship::Ship(const environments::Game& game) :
    GameObject(game)
{
}

Ship::~Ship(void)
{
}
#pragma endregion


#pragma region Public static methods
game_objects::sp_ship_t Ship::create(const environments::Game& game)
{
    game_objects::sp_ship_t new_ship{ new game_objects::Ship{ game } };
    auto asc = components::sprite::AnimatedSpriteComponent::create(new_ship->shared_from_this(), 100, 24);
    return new_ship;
}
#pragma endregion


#pragma region Public overridden methods
void Ship::update_actor(const float delta_time)
{
}
#pragma endregion


#pragma region Public methods
game_objects::speed_t Ship::get_down_speed(void) const noexcept
{
    return this->down_speed;
}
        
game_objects::speed_t Ship::get_right_speed(void) const noexcept
{
    return this->right_speed;
}

void Ship::process_keyboard(const uint8_t* state)
{
}
#pragma endregion
