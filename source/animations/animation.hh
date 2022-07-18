#pragma once


#include <textures/texture.hh>

#include <string>
#include <vector>


#include <animations/animations_typedef.hpp>


namespace animations
{
    class Animation
    {
    public:  // Public constructors, destructor and operators
        Animation(std::string name, const float fps, const bool looping, std::vector<textures::sp_texture_t> textures);
        Animation(const Animation& other);
        Animation(Animation&& other) noexcept;
        ~Animation(void);

        Animation& operator=(const Animation& other);
        Animation& operator=(Animation&& other) noexcept;

    private:  // Private attributes
        std::string anim_name;

        // Animation frame rate.
        // Allow different animation to run at different frame rates.
        // It also allows the animation to dynamically speed up or slow down
        float anim_fps = 24.0f;

        // Current frame displayed.
        // Allow you to also keep track of how long that frame has displayed
        float current_frame = 0.0f;

        bool looping = false;

        std::vector<textures::sp_texture_t> anim_textures;

    public:  // Public methods
        [[nodiscard]] size_t get_duration(void) const noexcept;

        [[nodiscard]] float get_fps(void) const noexcept;

        [[nodiscard]] std::string_view get_name_view(void) const noexcept;

        [[nodiscard]] textures::sp_texture_t get_texture(const size_t index) const;

        [[nodiscard]] const std::vector<textures::sp_texture_t>& get_textures_cref(void) const noexcept;

        float play(const float delta_time);

        void restart(void) noexcept;

        void set_fps(const float fps);

        // Set the textures used for animation
        void set_textures(std::vector<textures::sp_texture_t> textures);
    };
}
