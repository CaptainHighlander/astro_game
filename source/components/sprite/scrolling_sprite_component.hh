#pragma once 


#include <components/sprite/sprite_component.hh>
#include <vector2.hpp>

#include <SDL2/SDL_image.h>
#include <vector>


namespace components
{
    namespace sprite
    {
        class ScrollingSpriteComponent : public components::sprite::SpriteComponent
        {
        public:  // Public constructors, destructor and operator
            ScrollingSpriteComponent(const ScrollingSpriteComponent& other) = delete;
            ~ScrollingSpriteComponent(void);

            ScrollingSpriteComponent& operator=(const ScrollingSpriteComponent& other) = delete;

        protected:  // Protected constructors
            ScrollingSpriteComponent(game_objects::wp_game_object_t&& owner, const components::sprite::sprite_draw_order_t _draw_order = 10);

        private:  // Private attributes
            // Struct to encapsulate each scrolling image and its offset
            struct ScrollingTexture
            {
                SDL_Texture* texture = nullptr;
                Vector2 offset;
            };

            std::vector<ScrollingTexture> scrolling_textures;
            Vector2 screen_size;
            float scroll_speed = 0;

        public:  // Public override methods
            void draw(SDL_Renderer* renderer) override;

            void update(const float delta_time) override;

        public:  // Public methods
            [[nodiscard]] float get_scrool_speed(void) const noexcept;

            void set_screen_size(const Vector2& size);

            void set_scrool_speed(const float speed);

            // Set the textures used for background
            void set_textures(const std::vector<SDL_Texture*>& textures);
        };
    }
}