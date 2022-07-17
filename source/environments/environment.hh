#pragma once


#include <main_types.hpp>

#include <SDL2/SDL_render.h>


namespace environments
{
    class Environment
    {
    public:  // Public constructors, destructor and operators
        Environment(const Environment& other) = delete;
        virtual ~Environment(void);

        Environment& operator=(const Environment& other) = delete;

    protected:  // Protected constructors and operators
        explicit Environment(const Engine& engine);

    public:  // Public methods
        virtual void run(const uint8_t* keyboard_state, const float delta_time, SDL_Renderer& renderer) = 0;
    };
}
