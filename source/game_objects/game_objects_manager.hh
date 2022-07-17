#pragma once


#include <game_objects/game_objects_typedef.hpp>
#include <environments/environments_typedef.hpp>


#include <string>
#include <unordered_map>


namespace game_objects
{
    // TODO - creare classe
    typedef std::string ClassInfo;

    class GameObjectsManager
    {
    public:  // Public constructors, destructor and operators
        GameObjectsManager(void);
        GameObjectsManager(const GameObjectsManager& other) = delete;
        ~GameObjectsManager(void);

        GameObjectsManager& operator=(const GameObjectsManager& other) = delete;

    private:  // Private attributes
        std::unordered_map<std::string, game_objects::ClassInfo> classes_map;

    public:  // Public methods
        [[nodiscard]] game_objects::sp_game_object_t create_game_object(const environments::Game& game, const std::string class_name);
    };
}
