#pragma once


#include <environments/environment.hh>
#include <game_objects/game_objects_typedef.hpp>

#include <vector>


namespace environments
{
    class Game : public Environment
    {
    public:  // Public constructors, destructor and operators:
        Game(void);
        Game(const Game& other) = delete;
        virtual ~Game(void);
        
        Game& operator=(const Game& other) = delete;
    private:  // Private attributes
        std::vector<std::vector<game_objects::sp_game_object_t>> game_objects{ 2, std::vector<game_objects::sp_game_object_t>{ } };
        uint8_t game_objects_index = 0;
    public:  // Public methods
        void add_game_object(game_objects::sp_game_object_t game_object);

        virtual void update(const float delta_time) override;
    };
}