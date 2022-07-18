#include "animation.hh"
namespace ns = animations;


#pragma region Constructors, destructor and operators
ns::Animation::Animation(std::string name, const float fps, const bool _looping, std::vector<textures::sp_texture_t> textures) :
    anim_name(std::move(name)),
    anim_fps(fps), 
    looping(_looping), 
    anim_textures(std::move(textures))
{
}

ns::Animation::Animation(const ns::Animation& other) :
    anim_name(other.anim_name), 
    anim_fps(other.anim_fps), 
    current_frame(other.current_frame),
    looping(other.looping),
    anim_textures(other.anim_textures)
{
}

ns::Animation::Animation(ns::Animation&& other) noexcept :
    anim_name(std::move(other.anim_name)), 
    anim_fps(other.anim_fps), 
    current_frame(other.current_frame),
    looping(other.looping),
    anim_textures(std::move(other.anim_textures))
{
    other.anim_fps = -1.0f;
    other.current_frame = -1.0f;
}

ns::Animation::~Animation(void)
{
}

ns::Animation& ns::Animation::operator=(const ns::Animation& other)
{
    if (this != &other)
    {
        Animation tmp_animation{ other.anim_name, other.anim_fps, other.looping, other.anim_textures };
        *this = std::move(tmp_animation);
        this->current_frame = other.current_frame;
    }
    return *this;
}

ns::Animation& ns::Animation::operator=(ns::Animation&& other) noexcept
{
    if (this != &other)
    {
        this->anim_name = std::move(other.anim_name);

        this->anim_fps = other.anim_fps;
        other.anim_fps = -1.0f;

        this->current_frame = other.current_frame;
        other.current_frame = -1.0f;

        this->looping = other.looping;

        this->anim_textures = std::move(other.anim_textures);
    }
    return *this;
}
#pragma endregion


#pragma region Public methods
size_t ns::Animation::get_duration(void) const noexcept
{
    return this->anim_textures.size();
}

float ns::Animation::get_fps(void) const noexcept
{
    return this->anim_fps;
}

std::string_view ns::Animation::get_name_view(void) const noexcept
{
    return this->anim_name;
}

textures::sp_texture_t ns::Animation::get_texture(const size_t index) const
{
    return this->anim_textures.at(index);
}

const std::vector<textures::sp_texture_t>& ns::Animation::get_textures_cref(void) const noexcept
{
    return this->anim_textures;
}

float ns::Animation::play(const float delta_time)
{
    // Update the current frame based on frame rate and delta time
    this->current_frame += this->anim_fps * delta_time;
    
    // Wrap current frame if needed
    const auto animation_duration = this->anim_textures.size();
    while (this->current_frame >= animation_duration)
    {
        this->current_frame -= static_cast<float>(animation_duration);
    }    

    return this->current_frame;
}

void ns::Animation::restart(void) noexcept
{
    this->current_frame = 0.0f;
}

void ns::Animation::set_fps(const float fps)
{
    if (fps <= 0.0f)
        throw std::logic_error("invalid-animation-frame-rate");
    this->anim_fps = fps;
}

void ns::Animation::set_textures(std::vector<textures::sp_texture_t> textures)
{
    this->anim_textures = std::move(textures);
}
#pragma endregion
