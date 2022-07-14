#pragma once


#include <memory>


namespace environments
{
    class Environment;
    class Game;

    typedef std::shared_ptr<Environment> sp_environment_t;
}
