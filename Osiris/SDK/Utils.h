#pragma once

#include <tuple>
#include <numbers>

//shit
constexpr auto radiansToDegrees = [](float radians) constexpr noexcept { return radians * 180.0f / std::numbers::pi_v<float>; };

// pi constants.
constexpr float pi{ 3.14159265359f };
constexpr float rad_per_deg{ 0.01745329251f };
constexpr float deg_per_rad{ 57.2957795131f };

__forceinline float rad_to_deg(float x)
{
	return x * deg_per_rad;
}

__forceinline float deg_to_rad(float x)
{
	return x * rad_per_deg;
}

std::tuple<float, float, float> rainbowColor(float speed) noexcept;
