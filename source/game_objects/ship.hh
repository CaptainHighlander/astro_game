#pragma once


#include <game_objects/game_object.hh>


namespace game_objects
{
    class Ship : public game_objects::GameObject
    {
        friend class game_objects::GameObjectsManager;
    public:  // Public constructors, destructor and operators
        Ship(const Ship& other) = delete;
        Ship& operator=(const Ship& other) = delete;
        ~Ship(void);
    
    protected:  // Protected constructors
        Ship(const environments::Game& game, std::string_view class_name);

    private:  // Private attributes
        game_objects::speed_t right_speed = 0.0f;
        game_objects::speed_t down_speed = 0.0f;

    public:  // Public overriden methods
        void handle_keyboard_inputs(const uint8_t* keyboard_state) override;
        void update_game_object(const float delta_time) override;

    public:  // Public methods
        [[nodiscard]] game_objects::speed_t get_down_speed(void) const noexcept;
        
        [[nodiscard]] game_objects::speed_t get_right_speed(void) const noexcept;
        
    };
}
