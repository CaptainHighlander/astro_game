#include "game_object_creation_exception.hh"
namespace ns = game_objects::exceptions;


ns::GameObjectsCreationException::GameObjectsCreationException(std::string message) :
    runtime_error(std::move(message))
{
}
