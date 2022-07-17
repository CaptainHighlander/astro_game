#include "environment.hh"
namespace ns = environments;


#include <textures/texture_manager.hh>

#pragma region Constructors, destructor and operators:
ns::Environment::Environment(const Engine& engine)
{
    textures::TextureManager::init(engine);
}

ns::Environment::~Environment(void)
{
    textures::TextureManager::reset();
}
#pragma endregion
