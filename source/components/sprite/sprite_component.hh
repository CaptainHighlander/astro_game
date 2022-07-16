#pragma once


#include <components/component.hh>
#include <components/sprite/sprite_typedef.hpp>

#include <SDL2/SDL_image.h>


namespace components
{
    namespace sprite
    {
        class SpriteComponent : public components::Component
        {
        public:  // Public constructors, destructor and operator
            SpriteComponent(const SpriteComponent& other) = delete;
            ~SpriteComponent(void);

            SpriteComponent& operator=(const SpriteComponent& other) = delete;

        protected:  // Protected constructors
            SpriteComponent(game_objects::wp_game_object_t&& owner, const components::sprite::sprite_draw_order_t _draw_order = 100);
            
        protected:  // Protected attributes
            // Texture to draw
            SDL_Texture* texture = nullptr;

            // Draw order used for painter's algorithm
            components::sprite::sprite_draw_order_t draw_order = 100;

            // Width of texture
            components::sprite::sprite_width_t width = 0;

            // Height of texture
            components::sprite::sprite_height_t height = 0;

        public:  // Public methods
            virtual void draw(SDL_Renderer* renderer);

            virtual void set_texture(SDL_Texture* _texture);

            [[nodiscard]] components::sprite::sprite_draw_order_t get_draw_order(void) const noexcept;
            [[nodiscard]] components::sprite::sprite_height_t get_height(void) const noexcept;
            [[nodiscard]] components::sprite::sprite_width_t get_width(void) const noexcept;
        };
    }
}
