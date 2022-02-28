#include "vertex_t.h"
#include "../Helpers.h"
#include "Interfaces.h"

#pragma once

enum font_flags {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

namespace render
{

	void initialize();

	void draw_line(std::int32_t from_x, std::int32_t from_y, std::int32_t to_x, std::int32_t to_y, color color);
	void line(point_t a, point_t b, color c);
	void text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t* text, bool centered, color color);
	void circle(Vector center, color color, float r, float points);
	void Nigger(std::string preto);
	void text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color);
	void draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color);
	void draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color);
	void draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color);
	void draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color);
	Vector2 get_text_size(unsigned long font, std::string text);
	namespace fonts {
		extern unsigned long watermark_font;
		extern unsigned long Velocity;
		extern unsigned long Velocity2;
		extern unsigned long Keystrokes;
	}
}
