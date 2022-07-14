#pragma once


#include <main_types.hpp>

#include <SDL2/SDL_render.h>

#include <string>
#include <memory>
#include <unordered_map>



namespace components
{
    namespace sprite
    {
        class SpriteManager
        {
        public:  // Public constructors, destructor and operators
            SpriteManager(const SpriteManager& other) = delete;
            SpriteManager& operator=(const SpriteManager& other) = delete;
            ~SpriteManager(void);

        private:  // Private constructors
            explicit SpriteManager(std::shared_ptr<Engine>&& _engine);

        private:  // Private static attributes
            static std::unique_ptr<components::sprite::SpriteManager> sprite_manager;

        public:  // Public static methods
            [[nodiscard]] static bool init(std::shared_ptr<Engine> engine);
            [[nodiscard]] static SDL_Texture* load_texture(const std::string& file_name);
            [[nodiscard]] static SDL_Texture* load_texture(std::string&& file_name);

        private:  // Private attributes
            std::shared_ptr<Engine> engine;
            std::unordered_map<std::string, std::pair<uint32_t, SDL_Texture*>> textures_map;

        private:  // Private methods
            [[nodiscard]] SDL_Texture* load_texture(const std::string& file_name, const bool fake);
        };
    }
}
