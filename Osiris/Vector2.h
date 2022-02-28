#pragma once

#include <cmath>

class matrix3x4;

struct Vector2 {
    constexpr auto notNull2() const noexcept
    {
        return x || y || z;
    }

    constexpr auto operator==(const Vector2& v) const noexcept
    {
        return x == v.x && y == v.y && z == v.z;
    }

    constexpr auto operator!=(const Vector2& v) const noexcept
    {
        return !(*this == v);
    }

    constexpr Vector2& operator=(const float array[3]) noexcept
    {
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;
    }

    constexpr Vector2& operator+=(const Vector2& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr Vector2& operator+=(float f) noexcept
    {
        x += f;
        y += f;
        z += f;
        return *this;
    }

    constexpr Vector2& operator-=(const Vector2& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr Vector2& operator-=(float f) noexcept
    {
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }

    constexpr auto operator-(const Vector2& v) const noexcept
    {
        return Vector2{ x - v.x, y - v.y, z - v.z };
    }

    constexpr auto operator+(const Vector2& v) const noexcept
    {
        return Vector2{ x + v.x, y + v.y, z + v.z };
    }

    constexpr auto operator*(const Vector2& v) const noexcept
    {
        return Vector2{ x * v.x, y * v.y, z * v.z };
    }

    constexpr Vector2& operator/=(float div) noexcept
    {
        x /= div;
        y /= div;
        z /= div;
        return *this;
    }

    constexpr auto operator*(float mul) const noexcept
    {
        return Vector2{ x * mul, y * mul, z * mul };
    }

    constexpr auto operator-(float sub) const noexcept
    {
        return Vector2{ x - sub, y - sub, z - sub };
    }

    constexpr auto operator+(float add) const noexcept
    {
        return Vector2{ x + add, y + add, z + add };
    }

    constexpr void normalize2() noexcept
    {
        x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
        y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
        z = 0.0f;
    }

    auto length2() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    auto length2D2() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    constexpr auto squareLength2() const noexcept
    {
        return x * x + y * y + z * z;
    }

    constexpr auto dotProduct2(const Vector2& v) const noexcept
    {
        return x * v.x + y * v.y + z * v.z;
    }

    auto distTo(const Vector2& v) const noexcept
    {
        return (*this - v).length2();
    }

    float x, y, z;
};
