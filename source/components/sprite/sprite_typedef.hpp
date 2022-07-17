#pragma once

#include <cstdint>


namespace components
{
    namespace sprite
    {
        // Put here incomplete class definitions
        class AnimatedSpriteComponent;
        class ScrollingSpriteComponent;
        class SpriteComponent;
    }

    namespace sprite
    {
        typedef std::shared_ptr<AnimatedSpriteComponent> sp_animated_sprite_t;
        typedef std::weak_ptr<AnimatedSpriteComponent> wp_animated_sprite_t;

        typedef std::shared_ptr<ScrollingSpriteComponent> sp_scrolling_sprite_t;
        typedef std::weak_ptr<ScrollingSpriteComponent> wp_scrolling_sprite_t;

        typedef std::shared_ptr<SpriteComponent> sp_sprite_t;
        typedef std::weak_ptr<SpriteComponent> wp_sprite_t;

        typedef uint32_t draw_order_t;
        typedef uint32_t width_t;
        typedef components::sprite::width_t height_t;
    }
}
