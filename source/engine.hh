#pragma once


#include <string>

#include <SDL2/SDL.h>

#include <environments/environments_typedef.hpp>


class Engine
{
public:  // Public constructors, destructor and operators:
    explicit Engine(std::string&& _Engine_title);
    Engine(const Engine& other) = delete;
    ~Engine(void);
    
    Engine& operator=(const Engine& other) = delete;

private:  // Private attributes
    std::string title;
    bool b_is_running = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Uint32 ticks_count = 0;

    environments::sp_environment_t current_environment;

public:  // Public methods
    [[nodiscard]] SDL_Renderer* get_sdl_renderer_ptr(void) const noexcept;

    [[nodiscard]] bool initialize(void);

    void run_loop(void);

    void shutdown(void);

private:  // Private methods:
    [[nodiscard]] const uint8_t* process_inputs(void);
    void update(const uint8_t* keyboard_state);
};
