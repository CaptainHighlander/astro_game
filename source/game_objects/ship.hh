#pragma once


#include <game_objects/game_object.hh>


namespace game_objects
{
    class Ship : public game_objects::GameObject
    {
    public:  // Public constructors, destructor and operators
        Ship(const Ship& other) = delete;
        Ship& operator=(const Ship& other) = delete;
        ~Ship(void);
    
    protected:  // Protected constructors
        explicit Ship(const environments::Game& game);

    public:  // Public static methods
        [[nodiscard]] game_objects::sp_ship_t create(const environments::Game& game);

    private:  // Private attributes
        game_objects::speed_t right_speed = 0.0f;
        game_objects::speed_t down_speed = 0.0f;

    public:  // Public overriden methods
        void update_actor(const float delta_time) override;

    public:  // Public methods
        [[nodiscard]] game_objects::speed_t get_down_speed(void) const noexcept;
        
        [[nodiscard]] game_objects::speed_t get_right_speed(void) const noexcept;
        
        void process_keyboard(const uint8_t* state);
    };
}
