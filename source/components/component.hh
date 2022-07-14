#pragma once


#include <components/components_typedef.hpp>
#include <game_objects/game_objects_typedef.hpp>


namespace components
{
    class Component : public std::enable_shared_from_this<Component>
    {
    public:  // Public constructors, destructor and operator
        Component(const Component& other) = delete;
        virtual ~Component(void);

        Component& operator=(const Component& other) = delete;
        [[nodiscard]] virtual bool operator<(const Component& other) const noexcept;

    protected:  // Protected constructors
        Component(game_objects::wp_game_object_t&& owner, const uint32_t update_order = 100);

    protected:  // Protected attributes
        // Owning actor
        game_objects::wp_game_object_t owner;

        // Update order of component.
        // The lower the update order, the earlier the component updates
        uint32_t update_order = 100;
    public:  // Public methods
        // Update this component by delta time
        virtual void update(const float delta_time);

        [[nodiscard]] uint32_t get_update_order(void) const noexcept;
    };
}
