#pragma once

#include <cmath>

#include "SDK/matrix3x4.h"

struct vector2 {
    constexpr operator bool() const noexcept
    {
        return x || y || z;
    }

    constexpr vector2& operator=(const float array[3]) noexcept
    {
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;
    }

    constexpr vector2& operator+=(const vector2& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr vector2& operator-=(const vector2& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr auto operator-(const vector2& v) const noexcept
    {
        return vector2{ x - v.x, y - v.y, z - v.z };
    }

    constexpr auto operator+(const vector2& v) const noexcept
    {
        return vector2{ x + v.x, y + v.y, z + v.z };
    }

    constexpr vector2& operator/=(float div) noexcept
    {
        x /= div;
        y /= div;
        z /= div;
        return *this;
    }

    constexpr auto operator*(float mul) const noexcept
    {
        return vector2{ x * mul, y * mul, z * mul };
    }

    constexpr void normalize() noexcept
    {
        x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
        y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
        z = 0.0f;
    }

    auto length() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    auto length2D() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    constexpr auto squareLength() const noexcept
    {
        return x * x + y * y + z * z;
    }

    constexpr auto dotProduct(const vector2& v) const noexcept
    {
        return x * v.x + y * v.y + z * v.z;
    }

    constexpr auto transform(const matrix3x4& mat) const noexcept
    {
        return vector2{ dotProduct({ mat[0][0], mat[0][1], mat[0][2] }) + mat[0][3],
                       dotProduct({ mat[1][0], mat[1][1], mat[1][2] }) + mat[1][3],
                       dotProduct({ mat[2][0], mat[2][1], mat[2][2] }) + mat[2][3] };
    }

    float x, y, z;
};