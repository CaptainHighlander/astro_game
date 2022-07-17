#include "engine.hh"


#include <environments/game.hh>

#include <SDL2/SDL_image.h>


const uint16_t SCREEN_WIDTH = 1024;
const uint16_t SCREEN_HEIGHT = 768;


#pragma region Constructors, destructor and operators:
Engine::Engine(std::string&& _title) :
    title(std::move(_title))
{
}

Engine::~Engine(void)
{
    this->shutdown();
}
#pragma endregion


#pragma region Public methods:
SDL_Renderer* Engine::get_sdl_renderer_ptr(void) const noexcept
{
    return this->renderer;
}

bool Engine::initialize(void)
{
    // SDL library initialization
    const int sdl_result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (sdl_result != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Window creation
    this->window = SDL_CreateWindow(
        this->title.c_str(),  // Windows title
        100,
        100,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    if (this->window == nullptr)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create renderer
    this->renderer = SDL_CreateRenderer(
        this->window,  // Windows to create renderer for
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (this->renderer == nullptr)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        this->shutdown();
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Failed to init image handler");
        this->shutdown();
        return false;
    }

    // Create environment
    this->current_environment = environments::sp_environment_t{ new environments::Game{ *this } };

    // Engine loop can be runned
    this->b_is_running = true;

    return true;
}

void Engine::run_loop(void)
{
    while (this->b_is_running == true)
    {
        if (this->ticks_count != 0)
        {
            // Generate output: Swap front color-buffer and back color-buffer
            SDL_RenderPresent(this->renderer);

            // Frame limiting to 60 FPS: wait until 16 ms has elapsed since last frame
            while (SDL_TICKS_PASSED(SDL_GetTicks(), this->ticks_count + 16) == false)
                ;  // Wait
        }
        // Clear back color-buffer to a color (the engine's current color-buffer)
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(this->renderer);

        const auto* keyboard_state = this->process_inputs();
        this->update(keyboard_state);
    }
}

void Engine::shutdown(void)
{
    this->b_is_running = false;
    IMG_Quit();
    if (this->window != nullptr)
        SDL_DestroyWindow(this->window);
    if (this->renderer != nullptr)
        SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}
#pragma endregion


#pragma region Private methods:
const Uint8* Engine::process_inputs(void)
{
    // Pooling events on the WINDOW and handling some of them
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event) != 0)
    {
        switch (sdl_event.type)
        {
            case SDL_QUIT:  
                this->b_is_running = false;  // Close window
                break;
            default:  // Simple ignore other events
                break;
        }
    }

    // Handling keyboard inputs
    const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);  // Get a pointer to an array that contains the current state of the keyboard
    // Window
    if (keyboard_state[SDL_SCANCODE_ESCAPE] == 1)
        this->b_is_running = false;  // Close window

    return keyboard_state;
}

void Engine::update(const uint8_t* keyboard_state)
{
    // Get delta time (in seconds)
    float delta_time = static_cast<float>((SDL_GetTicks() - this->ticks_count)) / 1000.0f;
    this->ticks_count = SDL_GetTicks();

    // Clamp maximum delta time avoiding a delta time that's to high (for instance due to debugging breakpoints)
    if (delta_time > 0.05f)
        delta_time = 0.05f;

    // Update
    this->current_environment->run(keyboard_state, delta_time, *this->renderer);
}
#pragma endregion
