#pragma once

#include <cmath>

#include "../Helpers.h"
#include "Utils.h"

class matrix3x4;

#define CHECK_VALID( _v ) 0

enum
{
    PITCH = 0,
    YAW,
    ROLL
};

class matrix3x4;

struct Vector {
    constexpr auto notNull() const noexcept
    {
        return x || y || z;
    }

    Vector operator/(float flDivide) const
    {
        return Vector(this->x / flDivide, this->y / flDivide, this->z / flDivide);
    }

    constexpr auto operator==(const Vector& v) const noexcept
    {
        return x == v.x && y == v.y && z == v.z;
    }

    constexpr auto operator!=(const Vector& v) const noexcept
    {
        return !(*this == v);
    }

    constexpr Vector& operator=(const float array[3]) noexcept
    {
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;
    }

    constexpr Vector& operator+=(const Vector& v) noexcept
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr Vector& operator+=(float f) noexcept
    {
        x += f;
        y += f;
        z += f;
        return *this;
    }

    constexpr Vector& operator-=(const Vector& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr float& operator[](int i) {
		return ((float*)this)[i];
	}
    constexpr float operator[](int i) const {
		return ((float*)this)[i];
	}

    constexpr Vector& operator-=(float f) noexcept
    {
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }

    constexpr auto operator-(const Vector& v) const noexcept
    {
        return Vector{ x - v.x, y - v.y, z - v.z };
    }

    constexpr auto operator+(const Vector& v) const noexcept
    {
        return Vector{ x + v.x, y + v.y, z + v.z };
    }

    constexpr auto operator*(const Vector& v) const noexcept
    {
        return Vector{ x * v.x, y * v.y, z * v.z };
    }

    constexpr Vector& operator/=(float div) noexcept
    {
        x /= div;
        y /= div;
        z /= div;
        return *this;
    }

    constexpr auto operator*(float mul) const noexcept
    {
        return Vector{ x * mul, y * mul, z * mul };
    }

    constexpr auto operator-(float sub) const noexcept
    {
        return Vector{ x - sub, y - sub, z - sub };
    }

    constexpr auto operator+(float add) const noexcept
    {
        return Vector{ x + add, y + add, z + add };
    }

    constexpr Vector& normalize() noexcept
    {
        x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
        y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
        z = 0.0f;
        return *this;
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

    constexpr auto dotProduct(const Vector& v) const noexcept
    {
        return x * v.x + y * v.y + z * v.z;
    }

    constexpr auto transform(const matrix3x4& mat) const noexcept;

    auto distTo(const Vector& v) const noexcept
    {
        return (*this - v).length();
    }

    auto toAngle() const noexcept
    {
        return Vector{ radiansToDegrees(std::atan2(-z, std::hypot(x, y))),
                       radiansToDegrees(std::atan2(y, x)),
                       0.0f };
    }

    static auto fromAngle(const Vector& angle) noexcept
    {
        return Vector{ std::cos(Helpers::degreesToRadians(angle.x)) * std::cos(Helpers::degreesToRadians(angle.y)),
                       std::cos(Helpers::degreesToRadians(angle.x)) * std::sin(Helpers::degreesToRadians(angle.y)),
                      -std::sin(Helpers::degreesToRadians(angle.x)) };
    }

    float x, y, z;
};

#include "Matrix3x4.h"

constexpr auto Vector::transform(const matrix3x4& mat) const noexcept
{
    return Vector{ dotProduct({ mat[0][0], mat[0][1], mat[0][2] }) + mat[0][3],
                   dotProduct({ mat[1][0], mat[1][1], mat[1][2] }) + mat[1][3],
                   dotProduct({ mat[2][0], mat[2][1], mat[2][2] }) + mat[2][3] };
}