#pragma once

#include <concepts>
#include <mutex>
#include <numbers>
#include <random>
#include <string>
#include <vector>

#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include <DirectXMath.h>
#include "SDK/WeaponId.h"

#define M_DEG2RAD( x )		DirectX::XMConvertToRadians( x )

struct Color3;
struct Color4;
struct Vector;

constexpr float M_RADPI = 57.295779513082f;
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

namespace HitGroupz {
    enum {
        Invalid = -1,
        Generic,
        Head,
        Chest,
        Stomach,
        LeftArm,
        RightArm,
        LeftLeg,
        RightLeg,
        Gear = 10
    };
}

inline float FASTSQRT(float x)
{
    unsigned int i = *(unsigned int*)&x;

    i += 127 << 23;
    // approximation of square root
    i >>= 1;
    return *(float*)&i;
}

struct point_t
{
    int x, y;

    //point_t( ) : x( 0 ), y( 0 ) { };
    //point_t( int _x, int _y ) : x( _x ), y( _y ) { };

    point_t()
    {}

    point_t(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    point_t operator+(const point_t& p2)
    {
        return point_t(this->x + p2.x, this->y + p2.y);
    }

    point_t operator-(const point_t& p2)
    {
        return point_t(this->x - p2.x, this->y - p2.y);
    }

    point_t operator+(int a)
    {
        return point_t(this->x + a, this->y + a);
    }

    point_t operator-(int a)
    {
        return point_t(this->x - a, this->y - a);
    }

    point_t operator/(int a)
    {
        return point_t(this->x / a, this->y / a);
    }
};

using point = point_t;

struct color {
    int a, r, g, b;
    color() = default;
    color(const int r, const int g, const int b, const int a = 255) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    explicit color(const uint32_t color) {
        this->a = (color >> 24) & 0xff;
        this->r = (color >> 16) & 0xff;
        this->g = (color >> 8) & 0xff;
        this->b = (color & 0xff);
    }

    static color from_uint(const uint32_t uint) {
        return color(uint);
    }
    constexpr color& FromHSV(float h, float s, float v)
    {
        float colOut[3]{ };
        if (s == 0.0f)
        {
            r = g = b = static_cast<int>(v * 255);
            return *this;
        }

        h = std::fmodf(h, 1.0f) / (60.0f / 360.0f);
        int   i = static_cast<int>(h);
        float f = h - static_cast<float>(i);
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        switch (i)
        {
        case 0:
            colOut[0] = v;
            colOut[1] = t;
            colOut[2] = p;
            break;
        case 1:
            colOut[0] = q;
            colOut[1] = v;
            colOut[2] = p;
            break;
        case 2:
            colOut[0] = p;
            colOut[1] = v;
            colOut[2] = t;
            break;
        case 3:
            colOut[0] = p;
            colOut[1] = q;
            colOut[2] = v;
            break;
        case 4:
            colOut[0] = t;
            colOut[1] = p;
            colOut[2] = v;
            break;
        case 5: default:
            colOut[0] = v;
            colOut[1] = p;
            colOut[2] = q;
            break;
        }

        r = static_cast<int>(colOut[0] * 255);
        g = static_cast<int>(colOut[1] * 255);
        b = static_cast<int>(colOut[2] * 255);
        return *this;
    }

    static D3DCOLOR from_color(const color col) {
        return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
    }

    static color black(const int a = 255) { return { 0, 0, 0, a }; }
    static color white(const int a = 255) { return { 255, 255, 255, a }; }
    static color red(const int   a = 255) { return { 255, 0, 0, a }; }
    static color green(const int a = 255) { return { 0, 255, 0, a }; }
    static color blue(const int  a = 255) { return { 0, 0, 255, a }; }
};

namespace math
{ 
    void vector_angles(const Vector& forward, Vector& angles);
}

#define PI std::numbers::pi_v<float>

namespace Helpers
{

    constexpr auto degreesToRadians = [](float degrees) constexpr noexcept { return degrees * PI / 180.0f; };
    constexpr auto radiansToDegrees = [](float radians) constexpr noexcept { return radians * 180.0f / PI; };

    constexpr auto normalizeDeg = [](float a) noexcept { return std::isfinite(a) ? std::remainder(a, 360.0f) : 0.0f; };
    constexpr auto normalizeRad = [](float a) noexcept { return std::isfinite(a) ? std::remainder(a, PI * 2) : 0.0f; };

    constexpr float angleDiffRad(float a1, float a2) noexcept
    {
        float delta;

        delta = normalizeRad(a1 - a2);
        if (a1 > a2)
        {
            if (delta >= PI)
                delta -= PI * 2;
        }
        else
        {
            if (delta <= -PI)
                delta += PI * 2;
        }
        return delta;
    }

    const wchar_t* to_wchar(const char* string);
    unsigned int calculateColor(Color4 color) noexcept;
    unsigned int calculateColor(Color3 color) noexcept;
    float vector_normalize(Vector& v);
    Vector CalcAngle(Vector& src, Vector& dst);
    Vector CalcAngle2(const Vector& src, Vector& dst);
    void AverageDifference(const Vector& a, const Vector& b, float& result);
    void CalcAngle(Vector src, Vector dst, Vector& angles);

    unsigned int calculateColor(int r, int g, int b, int a) noexcept;
    void setAlphaFactor(float newAlphaFactor) noexcept;
    float getAlphaFactor() noexcept;
    void convertHSVtoRGB(float h, float s, float v, float& outR, float& outG, float& outB) noexcept;
    void healthColor(float fraction, float& outR, float& outG, float& outB) noexcept;
    unsigned int healthColor(float fraction) noexcept;

    template<class T, class U>
    static T clamp(const T& in, const U& low, const U& high)
    {
        if (in <= low)
            return low;

        if (in >= high)
            return high;

        return in;
    }

    _forceinline float NormalizeYaw(float f)
    {
        while (f < -180.0f)
            f += 360.0f;

        while (f > 180.0f)
            f -= 360.0f;

        return f;
    }

    constexpr auto units2meters(float units) noexcept
    {
        return units * 0.0254f;
    }

    ImWchar* getFontGlyphRanges() noexcept;

    constexpr int utf8SeqLen(char firstByte) noexcept
    {
        return (firstByte & 0x80) == 0x00 ? 1 :
               (firstByte & 0xE0) == 0xC0 ? 2 :
               (firstByte & 0xF0) == 0xE0 ? 3 :
               (firstByte & 0xF8) == 0xF0 ? 4 :
               -1;
    }

    std::wstring toWideString(const std::string& str) noexcept;
    std::wstring toUpper(std::wstring str) noexcept;

    bool decodeVFONT(std::vector<char>& buffer) noexcept;
    std::vector<char> loadBinaryFile(const std::string& path) noexcept;

    constexpr auto deg2rad(float degrees) noexcept { return degrees * (std::numbers::pi_v<float> / 180.0f); }
    constexpr auto rad2deg(float radians) noexcept { return radians * (180.0f / std::numbers::pi_v<float>); }

    [[nodiscard]] std::size_t calculateVmtLength(const std::uintptr_t* vmt) noexcept;

    constexpr auto isKnife(WeaponId id) noexcept
    {
        return (id >= WeaponId::Bayonet && id <= WeaponId::SkeletonKnife) || id == WeaponId::KnifeT || id == WeaponId::Knife;
    }

    [[nodiscard]] constexpr auto isMP5LabRats(WeaponId weaponID, int paintKit) noexcept
    {
        return weaponID == WeaponId::Mp5sd && paintKit == 800;
    }

    class RandomGenerator {
    public:
        template <std::integral T>
        [[nodiscard]] static T random(T min, T max) noexcept
        {
            std::scoped_lock lock{ mutex };
            return std::uniform_int_distribution{ min, max }(gen);
        }

        template <std::floating_point T>
        [[nodiscard]] static T random(T min, T max) noexcept
        {
            std::scoped_lock lock{ mutex };
            return std::uniform_real_distribution{ min, max }(gen);
        }

        template <typename T>
        [[nodiscard]] static std::enable_if_t<std::is_enum_v<T>, T> random(T min, T max) noexcept
        {
            return static_cast<T>(random(static_cast<std::underlying_type_t<T>>(min), static_cast<std::underlying_type_t<T>>(max)));
        }
    private:
        inline static std::mt19937 gen{ std::random_device{}() };
        inline static std::mutex mutex;
    };

    template <typename T>
    [[nodiscard]] T random(T min, T max) noexcept
    {
        return RandomGenerator::random(min, max);
    }
    const char* hitgroup_name(int hitgroup);

    template <typename t>
    static t lerp2(float progress, const t& t1, const t& t2)
    {
        return t1 + (t2 - t1) * progress;
    }
}
