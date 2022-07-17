#include "component.hh"
namespace ns = components;

#include <game_objects/game_object.hh>


#pragma region Constructors, destructor and operators
ns::Component::Component(game_objects::wp_game_object_t&& _owner, const uint32_t _update_order) :
    owner(std::move(_owner)), update_order(_update_order)
{
}

ns::Component::~Component(void)
{
    auto owner_sp = this->owner.lock();
    if (owner_sp)
        owner_sp->remove_component(shared_from_this());
}

bool ns::Component::operator<(const ns::Component& other) const noexcept
{
    return this->update_order < other.update_order;
}
#pragma endregion


#pragma region Public methods
void ns::Component::update(const float delta_time)
{
    // Nothing to do
}

uint32_t ns::Component::get_update_order(void) const noexcept
{
    return this->update_order;
}
#pragma endregion
