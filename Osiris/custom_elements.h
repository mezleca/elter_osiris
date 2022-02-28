#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include "../Osiris/imgui/imgui.h"
#include "../Osiris/imgui/imgui_internal.h"

using namespace ImGui;

class c_gui2
{
public:
    bool tab(const char* name, bool active, ImVec2 size_arg);
};

