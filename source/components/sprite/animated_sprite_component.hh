#pragma once


#include <animations/animations_typedef.hpp>
#include <components/sprite/sprite_component.hh>
#include <textures/textures_typedef.hpp>

#include <unordered_map>


namespace components
{
    namespace sprite
    {
        class AnimatedSpriteComponent : public components::sprite::SpriteComponent
        {
        public:  // Public constructors, destructor and operators
            AnimatedSpriteComponent(const AnimatedSpriteComponent& other) = delete;
            ~AnimatedSpriteComponent(void);

            AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent& other) = delete;
        
        protected:  // Protected constructor
            AnimatedSpriteComponent(game_objects::sp_game_object_t&& owner, const components::sprite::draw_order_t draw_oder);

        public:  // Public static members
            [[nodiscard]] static components::sprite::sp_animated_sprite_t create(game_objects::sp_game_object_t owner, const components::sprite::draw_order_t draw_oder);

        private:  // Private attributes
            // Animation to play
            std::string_view current_animation;

            // Animations
            std::unordered_map<std::string_view, animations::up_animation_t> animations;

        public:  // Public overridden methods
            // Update animation every frame
            void update(const float delta_time) override;

        public:  // Public methods
            void add_animation(animations::up_animation_t&& animation, const bool set_as_to_run);

            // Set animation to play
            void set_current_animation(std::string animation_name);
        };
    }
}
