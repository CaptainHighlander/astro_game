#pragma once


#include <memory>


namespace game_objects
{
    // Put here incomplete classes definitions
    class GameObject;
    class GameObjectsManager;
    class Ship;
}


namespace game_objects
{
    typedef std::shared_ptr<GameObject> sp_game_object_t;
    typedef std::weak_ptr<GameObject> wp_game_object_t;

    typedef std::shared_ptr<Ship> sp_ship_t;
    typedef std::weak_ptr<Ship> wp_ship_t;

    typedef float speed_t;

    typedef uint32_t unique_id_t;
}
