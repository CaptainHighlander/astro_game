#include "game.hh"
namespace ns = environments;

#include <game_objects/game_object.hh>


#pragma region Constructors, destructor and operators:
ns::Game::Game(void)
{
}

ns::Game::~Game(void)
{
}
#pragma endregion


#pragma region Public methods:
void ns::Game::add_game_object(game_objects::sp_game_object_t game_object)
{
    this->game_objects[(this->game_objects_index % 2) == 0].push_back(std::move(game_object));
}

void ns::Game::update(const float delta_time)
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
