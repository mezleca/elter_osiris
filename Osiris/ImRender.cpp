#include "ImRender.h"
#include "Hacks/Misc.h"
#define PI			3.14159265358979323846

void ImGuiRendering::BeginScene()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);


	ImGuiWindow* window = ImGui::GetCurrentWindow();


	if (interfaces->engine->isInGame() && interfaces->engine->isConnected())
	{

				g_MovementRecorder.MovementD();

	}
}

void ImGuiRendering::EndScene()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}

void ImGuiRendering::arc(float x, float y, float radius, float min_angle, float max_angle, Color col, float thickness) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
	window->DrawList->PathStroke(col.u32(), false, thickness);
}

void ImGuiRendering::DrawRing3D(int16_t x, int16_t y, int16_t z, int16_t radius, uint16_t points, Color color1, Color color2, float thickness)
{
	Vector pos = Vector(x, y, z);

	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
	{
		Vector start(radius * cosf(a) + pos.x, radius * sinf(a) + pos.y, pos.z);
		Vector end(radius * cosf(a + step) + pos.x, radius * sinf(a + step) + pos.y, pos.z);

		Vector start2d;
		Vector end2d;

		Vector Position;


		if (Helpers::WorldToScreen(start, start2d) &&
			Helpers::WorldToScreen(end, end2d) && Helpers::WorldToScreen(pos, Position))
		{

			DrawLine(start2d[0], start2d[1], end2d[0], end2d[1], color1);
			TriangleFilled(Position.x, Position.y, end2d.x, end2d.y, start2d.x, start2d.y, color2);
		}
	}
}

void ImGuiRendering::DrawCircle(float x, float y, float r, float s, Color color)
{
	float Step = PI * 2.0 / s;
	for (float a = 0; a < (PI * 2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;

		DrawLine(x1, y1, x2, y2, color);
	}
}

struct CUSTOMVERTEX {
	FLOAT x, y, z;
	FLOAT rhw;
	DWORD color;
};

void ImGuiRendering::DrawGradientCircle(float x, float y, float rad, float rotate, int type, int resolution, DWORD color, DWORD color2)
{
	


}


void ImGuiRendering::DrawString(float x, float y, Color color, int flags, ImFont* font, const char* message, ...)
{
	char output[1024] = {};
	va_list args;
	va_start(args, message);
	vsprintf_s(output, message, args);
	va_end(args);

	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->PushTextureID(font->ContainerAtlas->TexID);
	ImGui::PushFont(font);
	auto coord = ImVec2(x, y);
	auto size = ImGui::CalcTextSize(output);
	auto coord_out = ImVec2{ coord.x + 1.f, coord.y + 1.f };
	Color outline_clr = Color(0, 0, 0, color.a());

	int width = 0, height = 0;

	if (!(flags & render2::centered_x))
		size.x = 0;
	if (!(flags & render2::centered_y))
		size.y = 0;

	ImVec2 pos = ImVec2(coord.x - (size.x * .5), coord.y - (size.y * .5));

	if (flags & render2::outline)
	{
		pos.y++;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
		pos.x++;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
		pos.y--;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
		pos.x--;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
	}

	window->DrawList->AddText(pos, color.u32(), output);
	ImGui::PopFont();
}


void ImGuiRendering::DrawString2(float x, float y, Color color, int flags, ImFont* font, const std::string message, ...)
{
	char output[1024] = {};
	va_list args;
	va_start(args, message);
	vsprintf_s(output, message.c_str(), args);
	va_end(args);

	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->PushTextureID(font->ContainerAtlas->TexID);
	ImGui::PushFont(font);
	auto coord = ImVec2(x, y);
	auto size = ImGui::CalcTextSize(output);
	auto coord_out = ImVec2{ coord.x + 1.f, coord.y + 1.f };
	Color outline_clr = Color(0, 0, 0, color.a());

	int width = 0, height = 0;

	if (!(flags & render2::centered_x))
		size.x = 0;
	if (!(flags & render2::centered_y))
		size.y = 0;

	ImVec2 pos = ImVec2(coord.x - (size.x * .5), coord.y - (size.y * .5));

	if (flags & render2::outline)
	{
		pos.y++;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
		pos.x++;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
		pos.y--;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
		pos.x--;
		window->DrawList->AddText(pos, outline_clr.u32(), output);
	}

	window->DrawList->AddText(pos, color.u32(), output);
	ImGui::PopFont();
}


void ImGuiRendering::DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
	ImVec2 max = ImVec2(rightDownCorn.x, rightDownCorn.y);
	window->DrawList->AddRect(min, max, clr.u32(), 0.0F, -1, width);
}

void ImGuiRendering::DrawLine(float x1, float y1, float x2, float y2, Color clr, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr.u32(), thickness);
}

void ImGuiRendering::DrawLineGradient(float x1, float y1, float x2, float y2, Color clr1, Color cl2, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddRectFilledMultiColor(ImVec2(x1, y1), ImVec2(x2, y2),
		clr1.u32(), cl2.u32(), cl2.u32(), clr1.u32());
}

void ImGuiRendering::Rect(float x, float y, float w, float h, Color clr, float rounding)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), clr.u32(), rounding);
}

void ImGuiRendering::FilledRect(float x, float y, float w, float h, Color clr, float rounding)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), clr.u32(), rounding);
}

void ImGuiRendering::FilledRect2(float x, float y, float w, float h, Color clr, float rounding)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(w, h), clr.u32(), rounding);
}

void ImGuiRendering::Triangle(float x1, float y1, float x2, float y2, float x3, float y3, Color clr, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr.u32(), thickness);
}

void ImGuiRendering::TriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, Color clr)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr.u32());
}

void ImGuiRendering::QuadFilled(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Color clr)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddQuadFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImVec2(x4, y4), clr.u32());
}

void ImGuiRendering::CircleFilled(float x1, float y1, float radius, Color col, int segments)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddCircleFilled(ImVec2(x1, y1), radius, col.u32(), segments);
}

void ImGuiRendering::DrawWave(Vector loc, float radius, Color color, float thickness)
{
	static float Step = PI * 3.0f / 40;
	Vector prev;
	for (float lat = 0; lat <= PI * 3.0f; lat += Step)
	{
		float sin1 = sin(lat);
		float cos1 = cos(lat);
		float sin3 = sin(0.0f);
		float cos3 = cos(0.0f);

		Vector point1;
		point1 = Vector(sin1 * cos3, cos1, sin1 * sin3) * radius;
		Vector point3 = loc;
		Vector Out;
		point3 += point1;

		if (Helpers::WorldToScreen(point3, Out))
		{
			if (lat > 0.000f)
				DrawLine(prev.x, prev.y, Out.x, Out.y, color, thickness);
		}
		prev = Out;
	}
}