#pragma once


#include <vector>

#include <components/components_typedef.hpp>
#include <game_objects/game_objects_typedef.hpp>
#include <environments/environments_typedef.hpp>
#include <vector2.hpp>


namespace game_objects
{
    class GameObject : public std::enable_shared_from_this<GameObject>
    {
    public:  // Public enums
        // Used to track state of the game object
        enum class State
        {
            E_ACTIVE,
            E_PAUSED,   
            E_DEAD,
            E_TO_ERASE,
        };

    public:  // Public constructors, destructor and operators
        GameObject(const GameObject& other) = delete;
        virtual ~GameObject(void);

        GameObject& operator=(const GameObject& other) = delete;

    public:  // Protected static attributes
        static uint32_t next_id;

    protected:  // Protected constructors
        explicit GameObject(const environments::Game& game);

    public:  // Public static methods
        [[nodiscard]] static sp_game_object_t create(const environments::Game& game);

    private:  // Private attributes
        const environments::Game& game_cref;

        // GameObjects's ID
        uint32_t id = 0;

        // GameObject's state
        State state{ State::E_ACTIVE };

        // Center position of actor
        Vector2 position;

        // Uniform scale of actor (1.0f for 100%)
        float scale = 1.0f;

        // Rotation angle (in radians)
        float rotation = 0.0f;

        // Components held by this actor
        std::vector<components::sp_component_t> components;

    public:  // Public methods
        [[nodiscard]] Vector2 get_position(void) const noexcept;
        [[nodiscard]] float get_rotation(void) const noexcept;
        [[nodiscard]] float get_scale(void) const noexcept;
        [[nodiscard]] State get_state(void) const noexcept;

        [[nodiscard]] bool is_dead(void) const noexcept;
        [[nodiscard]] bool is_to_erase(void) const noexcept;

        virtual void update_actor(const float delta_time);

        void update(const float delta_time);
        void update_components(const float delta_time);

        void add_component(components::sp_component_t component_to_add);
        void remove_component(const components::sp_component_t& component);
    };
}
