#include "game.hh"
namespace ns = environments;

#include <game_objects/game_objects_manager.hh>
#include <game_objects/game_object.hh>


#include <cassert>


#pragma region Constructors, destructor and operators:
ns::Game::Game(const Engine& engine) :
    ns::Environment(engine),
    gobjs_manager( new game_objects::GameObjectsManager{ } )
{
    this->load_data();
}

ns::Game::~Game(void)
{
}
#pragma endregion


#pragma region Public overridden methods
void ns::Game::run(const uint8_t* keyboard_state, const float delta_time, SDL_Renderer& renderer)
{
    auto& game_objects_vec = this->game_objects[this->game_objects_index]; 

    while (game_objects_vec.empty() == false)
    {
        auto g_obj = game_objects_vec.back();
        if (g_obj && g_obj->is_to_erase() == false)
        {
            g_obj->handle_keyboard_inputs(keyboard_state);
            g_obj->update(delta_time);
            if (g_obj && g_obj->is_to_erase() == false)
            {
                g_obj->draw(renderer);
                this->game_objects[(this->game_objects_index % 2) == 0].push_back(std::move(g_obj));
            }
        }
        game_objects_vec.pop_back();
    } 

    // Go to next element of circular vector
    this->game_objects_index += 1;
    if (this->game_objects_index > 1)
        this->game_objects_index = 0;
}
#pragma endregion


#pragma region Public methods:
void ns::Game::add_game_object(const std::string& class_name)
{
    auto new_gobj = this->gobjs_manager->create_game_object(*this, class_name);
    this->game_objects[(this->game_objects_index % 2) == 0].push_back(std::move(new_gobj));
}

void ns::Game::load_data(void)
{
    auto new_stars = this->gobjs_manager->create_game_object(*this, "stars");
	new_stars->set_position(512.0f, 384.0f);
    this->game_objects[this->game_objects_index].push_back(new_stars);

    auto new_farback = this->gobjs_manager->create_game_object(*this, "farback");
	new_farback->set_position(512.0f, 384.0f);
    this->game_objects[this->game_objects_index].push_back(new_farback);

	// Create player's ship
    auto new_ship = this->gobjs_manager->create_game_object(*this, "ship");
	new_ship->set_position(100.0f, 384.0f);
	new_ship->set_scale(1.5f);
    this->game_objects[this->game_objects_index].push_back(new_ship);

    // Create player's ship
    auto new_ship2 = this->gobjs_manager->create_game_object(*this, "ship");
	new_ship2->set_position(150.0f, 0.0f);
	new_ship2->set_scale(3.0f);
    this->game_objects[this->game_objects_index].push_back(new_ship2);
}
#pragma endregion
