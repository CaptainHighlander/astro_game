#pragma once

struct Vector2
{
    float x = 0;
    float y = 0;
    
    Vector2(void) = default;
    Vector2(const float _x, const float _y) : x(_x), y(_y) { }
};
