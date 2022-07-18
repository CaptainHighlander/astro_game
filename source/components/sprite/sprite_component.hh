#pragma once


#include <components/component.hh>
#include <components/sprite/sprite_typedef.hpp>
#include <textures/textures_typedef.hpp>

#include <SDL2/SDL_render.h>


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
            bool operator<(const SpriteComponent& other) const noexcept;
            bool operator>(const SpriteComponent& other) const noexcept;

        protected:  // Protected constructors
            SpriteComponent(game_objects::wp_game_object_t&& owner, const components::sprite::draw_order_t _draw_order = 100);
            
        protected:  // Protected attributes
            // Texture to draw
            textures::sp_texture_t texture;

            // Draw order used for painter's algorithm
            components::sprite::draw_order_t draw_order = 100;

        public:  // Public methods
            virtual void draw(SDL_Renderer& renderer);

            virtual void set_texture(textures::sp_texture_t texture);

            [[nodiscard]] components::sprite::draw_order_t get_draw_order(void) const noexcept;

            [[nodiscard]] components::sprite::height_t get_height(void) const noexcept;
            
            [[nodiscard]] components::sprite::width_t get_width(void) const noexcept;
        };
    }
}
