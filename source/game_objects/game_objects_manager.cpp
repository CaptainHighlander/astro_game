#include "game_objects_manager.hh"
namespace ns = game_objects;


#include <components/sprite/animated_sprite_component.hh>
#include <components/sprite/scrolling_sprite_component.hh>

#include <game_objects/exceptions/game_object_creation_exception.hh>
#include <game_objects/game_object.hh>
#include <game_objects/ship.hh>

#include <textures/texture_manager.hh>

#include <vector>


#pragma region Constructors, destructor and operators
ns::GameObjectsManager::GameObjectsManager(void)
{
    this->classes_map = std::unordered_map<std::string, ClassInfo>{
        { "ship", "ship" },
        { "farback", "farback" },
        { "stars", "stars" },
    };
}

ns::GameObjectsManager::~GameObjectsManager(void)
{
}
#pragma endregion


#pragma region Public methods
ns::sp_game_object_t ns::GameObjectsManager::create_game_object(const environments::Game& game, const std::string class_name)
{
    const auto class_interator = this->classes_map.find(class_name);
    if (class_interator == this->classes_map.cend())
        throw ns::exceptions::GameObjectsCreationException("class " + class_name + " not-found");

    ns::sp_game_object_t new_game_object;

    const std::string& class_key = class_interator->first;
    const ClassInfo& class_info = class_interator->second;
   
    if (class_info == "ship")
    {
        new_game_object = ns::sp_game_object_t{
            new ns::Ship{ game, class_key }
        };
        auto asc = components::sprite::AnimatedSpriteComponent::create(new_game_object, 120, 24);
        std::vector<textures::sp_texture_t> anims{
            textures::TextureManager::load_texture("assets/textures/ship/ship01.png"),
            textures::TextureManager::load_texture("assets/textures/ship/ship02.png"),
            textures::TextureManager::load_texture("assets/textures/ship/ship03.png"),
            textures::TextureManager::load_texture("assets/textures/ship/ship04.png"),
        };
        asc->set_animation_textures(std::move(anims));
        new_game_object->sprite = asc;
        new_game_object->add_component(std::move(asc));
    }
    else if (class_info == "farback")
    {
        new_game_object = ns::sp_game_object_t{
            new ns::GameObject{ game, class_key }
        };
        auto bg = components::sprite::ScrollingSpriteComponent::create(new_game_object, 100);
        bg->set_screen_size(Vector2(1024.0f, 768.0f));
        std::vector<textures::sp_texture_t> bgtexs{
            textures::TextureManager::load_texture("assets/textures/farback/farback01.png"),
            textures::TextureManager::load_texture("assets/textures/farback/farback02.png"),
        };
        bg->set_textures(bgtexs);
        bg->set_scrool_speed(-100.0f);
        new_game_object->sprite = bg;
        new_game_object->add_component(std::move(bg));
    }
    else if (class_info == "stars")
    {
        new_game_object = ns::sp_game_object_t{
            new ns::GameObject{ game, class_key }
        };
        auto bg = components::sprite::ScrollingSpriteComponent::create(new_game_object, 50);
        bg->set_screen_size(Vector2(1024.0f, 768.0f));
        std::vector<textures::sp_texture_t> bgtexs{
            textures::TextureManager::load_texture("assets/textures/stars/stars.png"),
            textures::TextureManager::load_texture("assets/textures/stars/stars.png"),
        };
        bg->set_textures(bgtexs);
        bg->set_scrool_speed(-200.0f);
        new_game_object->sprite = bg;
        new_game_object->add_component(std::move(bg));
    }
    else
    {
        new_game_object = ns::sp_game_object_t{
            new ns::GameObject{ game, class_key }
        };
    }

    return new_game_object;
}
#pragma endregion
