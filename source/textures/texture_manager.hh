#pragma once


#include <main_types.hpp>
#include <textures/textures_typedef.hpp>


#include <SDL2/SDL_render.h>


#include <string>
#include <memory>
#include <unordered_map>



namespace textures
{
    class TextureManager
    {
        friend textures::Texture;
    public:  // Public constructors, destructor and operators
        TextureManager(const TextureManager& other) = delete;
        TextureManager& operator=(const TextureManager& other) = delete;
        ~TextureManager(void);

    private:  // Private constructors
        explicit TextureManager(const Engine& engine);

    private:  // Private static attributes
        static std::unique_ptr<textures::TextureManager> texture_manager;

    public:  // Public static methods
        static bool init(const Engine& engine);
        [[nodiscard]] static textures::sp_texture_t load_texture(const std::string& file_name);
        [[nodiscard]] static textures::sp_texture_t load_texture(std::string&& file_name);

        static bool reset(void);

    private:  // Private static methods
        static void remove_texture(const std::string& file_name);

    private:  // Private attributes
        const Engine& engine;
        std::unordered_map<std::string, std::pair<uint32_t, SDL_Texture*>> textures_map;

    private:  // Private methods
        [[nodiscard]] textures::sp_texture_t load_texture_int(const std::string& file_name);
        void remove_texture_int(const std::string& file_name);
    };
}
