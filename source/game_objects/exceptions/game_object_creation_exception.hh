#pragma once


#include <stdexcept>


namespace game_objects
{
    namespace exceptions
    {
        class GameObjectsCreationException : std::runtime_error
        {
        public:
            explicit GameObjectsCreationException(std::string message);
        };
    }
}
