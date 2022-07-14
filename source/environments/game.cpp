#include "game.hh"
using namespace environments;

#include <game_objects/game_object.hh>
#include <iostream>


#pragma region Constructors, destructor and operators:
Game::Game(void)
{
}

Game::~Game(void)
{
}
#pragma endregion


#pragma region Public methods:
void Game::add_game_object(game_objects::sp_game_object_t game_object)
{
    std::cout << std::to_string((this->game_objects_index % 2) == 0) << std::endl;
    this->game_objects[(this->game_objects_index % 2) == 0].push_back(std::move(game_object));
}

void Game::update(const float delta_time)
{
    auto& game_objects_vec = this->game_objects[this->game_objects_index]; 

    while (game_objects_vec.empty() == false)
    {
        auto g_obj = game_objects_vec.back();
        if (g_obj && g_obj->is_to_erase() == false)
        {
            g_obj->update(delta_time);
            this->add_game_object(std::move(g_obj));
        }
        game_objects_vec.pop_back();
    } 

    // Go to next element of circular vector
    this->game_objects_index += 1;
    if (this->game_objects_index > 1)
        this->game_objects_index = 0;
}
#pragma endregion
