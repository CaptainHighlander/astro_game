#pragma once


#include <components/sprite/sprite_component.hh>


#include <vector>


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
            AnimatedSpriteComponent(game_objects::sp_game_object_t&& owner, const components::sprite::sprite_draw_order_t draw_oder, const float anim_fps);

        public:  // Public static members
            [[nodiscard]] static components::sprite::sp_animated_sprite_t create(game_objects::sp_game_object_t owner, const components::sprite::sprite_draw_order_t draw_oder, const float anim_fps);

        private:  // Private attributes
            // All textures in the animation
            std::vector<SDL_Texture*> anim_textures;

            // Current frame displayed.
            // Allow you to also keep track of how log that frame has displayed
            float current_frame = 0.0f;

            // Animation frame rate.
            // Allow different animated prites to run at different frame rates.
            // It alo allows the animation to dynamically speed up or slow down
            float anim_fps = 0.0f;

        public:  // Public overridden methods
            // Update animation every frame
            void update(const float delta_time) override;

        public:  // Public methods
            [[nodiscard]] float get_anim_fps(void) const noexcept;

            void set_anim_fps(float anim_fps);

            // Set the textures usd for animation
            void set_animation_textures(std::vector<SDL_Texture*>&& textures);
        };
    }
}
