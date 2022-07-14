#pragma once


#include <memory>

#include <components/sprite/sprite_typedef.hpp>


namespace components
{
    class Component;
    class ComponentFactory;

    typedef std::shared_ptr<Component> sp_component_t;
    typedef std::weak_ptr<Component> wp_component_t;
}
