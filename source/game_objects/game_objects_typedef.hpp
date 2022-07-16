#pragma once


#include <memory>


namespace game_objects
{
    class GameObject;
    class Ship;

    typedef std::shared_ptr<GameObject> sp_game_object_t;
    typedef std::weak_ptr<GameObject> wp_game_object_t;

    typedef std::shared_ptr<Ship> sp_ship_t;
    typedef std::weak_ptr<Ship> wp_ship_t;

    typedef float speed_t;
}
