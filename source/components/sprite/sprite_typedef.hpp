#pragma once

#include <cstdint>


namespace components
{
    namespace sprite
    {
        class AnimatedSpriteComponent;

        typedef std::shared_ptr<AnimatedSpriteComponent> sp_animated_sprite_t;
        typedef std::weak_ptr<AnimatedSpriteComponent> wp_animated_sprite_t;

        typedef uint32_t sprite_draw_order_t;
        typedef uint32_t sprite_width_t;
        typedef sprite_width_t sprite_height_t;
    }
}
