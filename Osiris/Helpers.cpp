#include <array>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cwctype>
#include <fstream>
#include <random>
#include <span>
#include <string_view>
#include <unordered_map>
#include <algorithm>
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "imgui/imgui.h"

#include "ConfigStructs.h"
#include "GameData.h"
#include "Helpers.h"
#include "Memory.h"
#include "SDK/GlobalVars.h"
#include "Interfaces.h"
#include "../SDK/Engine.h"
#include <DirectXMath.h>

static auto rainbowColor(float time, float speed, float alpha) noexcept
{
    constexpr float pi = std::numbers::pi_v<float>;
    return std::array{ std::sin(speed * time) * 0.5f + 0.5f,
                       std::sin(speed * time + 2 * pi / 3) * 0.5f + 0.5f,
                       std::sin(speed * time + 4 * pi / 3) * 0.5f + 0.5f,
                       alpha };
}

static float alphaFactor = 1.0f;

typedef float vec_t;

inline vec_t BitsToFloat(unsigned long i)
{
    return *reinterpret_cast<vec_t*>(&i);
}

Vector Helpers::CalcAngle2(const Vector& src, Vector& dst)
{
    Vector vAngle;
    Vector delta((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));
    double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

    vAngle.x = float(atanf(float(delta.z / hyp)) * 57.295779513082f);
    vAngle.y = float(atanf(float(delta.y / delta.x)) * 57.295779513082f);
    vAngle.z = 0.0f;

    if (delta.x >= 0.0)
        vAngle.y += 180.0f;

    return vAngle;
}

void Helpers::AverageDifference(const Vector& a, const Vector& b, float& result)
{
    Vector calcvec;
    calcvec.x = abs(a.x - b.x);
    calcvec.y = abs(a.y - b.y);
    calcvec.z = abs(a.y - b.y);

    result = (calcvec.x + calcvec.y + calcvec.z) / 3.f;
}

void math::vector_angles(const Vector& forward, Vector& angles) {
    Vector view;

    if (!forward[0] && !forward[1])
    {
        view[0] = 0.0f;
        view[1] = 0.0f;
    }
    else
    {
        view[1] = atan2(forward[1], forward[0]) * 180.0f / M_PI;

        if (view[1] < 0.0f)
            view[1] += 360.0f;

        view[2] = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
        view[0] = atan2(forward[2], view[2]) * 180.0f / M_PI;
    }

    angles[0] = -view[0];
    angles[1] = view[1];
    angles[2] = 0.f;
}

Vector cross_product(const Vector& a, const Vector& b)
{
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

void vector_angles(const Vector& forward, Vector& up, Vector& angles)
{
    auto left = cross_product(up, forward);
    left.normalize();

    auto forwardDist = forward.length2D();

    if (forwardDist > 0.001f)
    {
        angles.x = atan2(-forward.z, forwardDist) * 180.0f / M_PI;
        angles.y = atan2(forward.y, forward.x) * 180.0f / M_PI;

        auto upZ = (left.y * forward.x) - (left.x * forward.y);
        angles.z = atan2(left.z, upZ) * 180.0f / M_PI;
    }
    else
    {
        angles.x = atan2(-forward.z, forwardDist) * 180.0f / M_PI;
        angles.y = atan2(-left.x, left.y) * 180.0f / M_PI;
        angles.z = 0.0f;
    }
}

void Helpers::CalcAngle(Vector src, Vector dst, Vector& angles)
{
  
}

unsigned int Helpers::calculateColor(Color4 color) noexcept
{
    color.color[3] *= alphaFactor;

   // if (!config->ignoreFlashbang)
        color.color[3] *= (255.0f - GameData::local().flashDuration) / 255.0f;
    return ImGui::ColorConvertFloat4ToU32(color.rainbow ? rainbowColor(memory->globalVars->realtime, color.rainbowSpeed, color.color[3]) : color.color);
}

unsigned int Helpers::calculateColor(Color3 color) noexcept
{
    return ImGui::ColorConvertFloat4ToU32(color.rainbow ? rainbowColor(memory->globalVars->realtime, color.rainbowSpeed, 1.0f) : ImVec4{ color.color[0], color.color[1], color.color[2], 1.0f});
}


float Helpers::vector_normalize(Vector& v) {
    float l = v.length();

    if (l != 0.0f) //-V550
        v /= l;
    else
    {
        v.x = v.y = 0.0f;
        v.z = 1.0f;
    }

    return l;
}
//--------------------------------------------------------------------------------




const wchar_t* Helpers::to_wchar(const char* string) {
    va_list va_alist;
    char buf[1024];
    va_start(va_alist, string);
    _vsnprintf_s(buf, sizeof(buf), string, va_alist);
    va_end(va_alist);
    wchar_t wbuf[1024];
    MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

    return wbuf;
}

unsigned int Helpers::calculateColor(int r, int g, int b, int a) noexcept
{
    a -= static_cast<int>(a * GameData::local().flashDuration / 255.0f);
    return IM_COL32(r, g, b, a * alphaFactor);
}

void Helpers::setAlphaFactor(float newAlphaFactor) noexcept
{
    alphaFactor = newAlphaFactor;
}

float Helpers::getAlphaFactor() noexcept
{
    return alphaFactor;
}

void Helpers::convertHSVtoRGB(float h, float s, float v, float& outR, float& outG, float& outB) noexcept
{
    ImGui::ColorConvertHSVtoRGB(h, s, v, outR, outG, outB);
}

void Helpers::healthColor(float fraction, float& outR, float& outG, float& outB) noexcept
{
    constexpr auto greenHue = 1.0f / 3.0f;
    constexpr auto redHue = 0.0f;
    convertHSVtoRGB(std::lerp(redHue, greenHue, fraction), 1.0f, 1.0f, outR, outG, outB);
}

unsigned int Helpers::healthColor(float fraction) noexcept
{
    float r, g, b;
    healthColor(fraction, r, g, b);
    return calculateColor(static_cast<int>(r * 255.0f), static_cast<int>(g * 255.0f), static_cast<int>(b * 255.0f), 255);
}

ImWchar* Helpers::getFontGlyphRanges() noexcept
{
    static ImVector<ImWchar> ranges;
    if (ranges.empty()) {
        ImFontGlyphRangesBuilder builder;
        constexpr ImWchar baseRanges[]{
            0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
            0x0300, 0x03FF, // Combining Diacritical Marks + Greek/Coptic
            0x0600, 0x06FF, // Arabic
            0x0E00, 0x0E7F, // Thai
            0
        };
        builder.AddRanges(baseRanges);
        builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
        builder.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
        builder.AddText("\u9F8D\u738B\u2122");
        builder.BuildRanges(&ranges);
    }
    return ranges.Data;
}

std::wstring Helpers::toWideString(const std::string& str) noexcept
{
    std::wstring wide(str.length(), L'\0');
    if (const auto newLen = std::mbstowcs(wide.data(), str.c_str(), wide.length()); newLen != static_cast<std::size_t>(-1))
        wide.resize(newLen);
    return wide;
}

static void toUpper(std::span<wchar_t> str) noexcept
{
    static std::unordered_map<wchar_t, wchar_t> upperCache;

    for (auto& c : str) {
        if (c >= 'a' && c <= 'z') {
            c -= ('a' - 'A');
        } else if (c > 127) {
            if (const auto it = upperCache.find(c); it != upperCache.end()) {
                c = it->second;
            } else {
                const auto upper = std::towupper(c);
                upperCache.emplace(c, upper);
                c = upper;
            }
        }
    }
}

std::wstring Helpers::toUpper(std::wstring str) noexcept
{
    ::toUpper(str);
    return str;
}

bool Helpers::decodeVFONT(std::vector<char>& buffer) noexcept
{
    constexpr std::string_view tag = "VFONT1";
    unsigned char magic = 0xA7;

    if (buffer.size() <= tag.length())
        return false;

    const auto tagIndex = buffer.size() - tag.length();
    if (std::memcmp(tag.data(), &buffer[tagIndex], tag.length()))
        return false;

    unsigned char saltBytes = buffer[tagIndex - 1];
    const auto saltIndex = tagIndex - saltBytes;
    --saltBytes;

    for (std::size_t i = 0; i < saltBytes; ++i)
        magic ^= (buffer[saltIndex + i] + 0xA7) % 0x100;

    for (std::size_t i = 0; i < saltIndex; ++i) {
        unsigned char xored = buffer[i] ^ magic;
        magic = (buffer[i] + 0xA7) % 0x100;
        buffer[i] = xored;
    }

    buffer.resize(saltIndex);
    return true;
}

std::vector<char> Helpers::loadBinaryFile(const std::string& path) noexcept
{
    std::vector<char> result;
    std::ifstream in{ path, std::ios::binary };
    if (!in)
        return result;
    in.seekg(0, std::ios_base::end);
    result.resize(static_cast<std::size_t>(in.tellg()));
    in.seekg(0, std::ios_base::beg);
    in.read(result.data(), result.size());
    return result;
}

std::size_t Helpers::calculateVmtLength(const std::uintptr_t* vmt) noexcept
{
    std::size_t length = 0;
#ifdef _WIN32
    MEMORY_BASIC_INFORMATION memoryInfo;
    while (VirtualQuery(LPCVOID(vmt[length]), &memoryInfo, sizeof(memoryInfo)) && memoryInfo.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))
        ++length;
#else
    while (vmt[length])
        ++length;
#endif
    return length;
}
