#pragma once


#include <components/components_typedef.hpp>
#include <environments/environment.hh>
#include <game_objects/game_objects_typedef.hpp>

#include <SDL2/SDL_render.h>

#include <vector>


namespace environments
{
    class Game : public Environment
    {
    public:  // Public constructors, destructor and operators:
        explicit Game(const Engine& engine);
        Game(const Game& other) = delete;
        virtual ~Game(void);
        
        Game& operator=(const Game& other) = delete;

    private:  // Private attributes
        uint8_t game_objects_index = 0;
        std::vector<std::vector<game_objects::sp_game_object_t>> game_objects{ 2, std::vector<game_objects::sp_game_object_t>{ } };

        std::unique_ptr<game_objects::GameObjectsManager> gobjs_manager;

    public:  // Public overridden methods
        void run(const uint8_t* keyboard_state, const float delta_time, SDL_Renderer& renderer) override;

    public:  // Public methods
        void add_game_object(const std::string& class_name);

        void load_data(void);

    private:  // Private methods
        void draw(SDL_Renderer& renderer, std::vector<components::sprite::sp_sprite_t>&& sprites_to_draw);
    };
}