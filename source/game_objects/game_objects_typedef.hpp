#pragma once


#include <memory>


namespace game_objects
{
    class GameObject;

    typedef std::shared_ptr<GameObject> sp_game_object_t;
    typedef std::weak_ptr<GameObject> wp_game_object_t;
}
