#pragma once

#include <cstdint>


namespace components
{
    namespace sprite
    {
        class AnimatedSpriteComponent;

        typedef std::shared_ptr<AnimatedSpriteComponent> sp_animated_sprite_t;
        typedef std::weak_ptr<AnimatedSpriteComponent> wp_animated_sprite_t;

        typedef uint32_t draw_order_t;
        typedef uint32_t width_t;
        typedef components::sprite::width_t height_t;
    }
}
