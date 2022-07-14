#pragma once


namespace math_plus
{
    const float PI = 3.1415926535f;

	[[nodiscard]] inline float to_radians(const float degrees)
	{
		return degrees * PI / 180.0f;
	}


	[[nodiscard]] inline float to_degrees(const float radians, const bool clockwise)
	{
		float degrees = radians * 180.0f / PI;
		return (clockwise == false) ? degrees : -degrees;
	}
}
