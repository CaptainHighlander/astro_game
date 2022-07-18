#pragma once


#include <components/components_typedef.hpp>
#include <game_objects/game_objects_typedef.hpp>
#include <environments/environments_typedef.hpp>
#include <vector2.hpp>

#include <string>
#include <vector>


namespace game_objects
{
    class GameObject
    {
        friend class game_objects::GameObjectsManager;
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

    protected:  // Protected constructors
        GameObject(const environments::Game& game, std::string_view class_name);

    protected:  // Protected static attributes
        static game_objects::unique_id_t next_id;

    protected:  // Protected attributes
        // Center position of actor
        Vector2 position;
    private:  // Private attributes
        const environments::Game& game_cref;

        // Game object class
        std::string_view class_name;

        // GameObjects's ID
        game_objects::unique_id_t unique_id = 0;

        // GameObject's state
        State state{ State::E_ACTIVE };

        // Uniform scale of actor (1.0f for 100%)
        float scale = 1.0f;

        // Rotation angle (in radians)
        float rotation = 0.0f;

        // Components held by this actor
        std::vector<components::sp_component_t> components;

        // Sprite component
        components::sprite::sp_sprite_t sprite;

    public:  // Public methods
        void add_component(components::sp_component_t component_to_add);

        [[nodiscard]] Vector2 get_position(void) const noexcept;

        [[nodiscard]] float get_rotation(void) const noexcept;

        [[nodiscard]] float get_scale(void) const noexcept;

        [[nodiscard]] components::sprite::sp_sprite_t get_sprite_component(void) const noexcept;

        [[nodiscard]] State get_state(void) const noexcept;

        virtual void handle_keyboard_inputs(const uint8_t* keyboard_state);

        [[nodiscard]] bool is_dead(void) const noexcept;
        [[nodiscard]] bool is_to_erase(void) const noexcept;

        void remove_component(const components::sp_component_t& component);

        void set_position(const float x, const float y);
        void set_scale(const float scale);
        
        void update(const float delta_time);

    protected:  // Protected methods
        void update_components(const float delta_time);
        virtual void update_game_object(const float delta_time);
    };
}
