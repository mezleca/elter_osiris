#include "render.h"

unsigned long render::fonts::watermark_font;
unsigned long render::fonts::Velocity;
unsigned long render::fonts::Velocity2;
unsigned long render::fonts::Keystrokes;

void render::initialize() {
	render::fonts::watermark_font = interfaces->surface->createFont();
	render::fonts::Velocity = interfaces->surface->createFont();
	render::fonts::Velocity2 = interfaces->surface->createFont();
	render::fonts::Keystrokes = interfaces->surface->createFont();

	interfaces->surface->setFontGlyphSet(render::fonts::watermark_font, "Tahoma", 12, 400, 0, 0, font_flags::fontflag_dropshadow);
	interfaces->surface->setFontGlyphSet(render::fonts::Velocity, "Verdana", 34, 700, 0, 0, font_flags::fontflag_antialias);
	interfaces->surface->setFontGlyphSet(render::fonts::Velocity2, "Verdana", 34, 700, 0, 0, font_flags::fontflag_none | font_flags::fontflag_antialias);
	interfaces->surface->setFontGlyphSet(render::fonts::Keystrokes, "Tahoma", 22, 800, 0, 0, font_flags::fontflag_dropshadow);

}

void render::draw_line(std::int32_t x1, std::int32_t y1, std::int32_t x2, std::int32_t y2, color colour) {
	interfaces->surface->setDrawColor(colour.r, colour.g, colour.b, colour.a);
	interfaces->surface->drawLine(x1, y1, x2, y2);
}


void render::line(point_t a, point_t b, color c)
{
	interfaces->surface->setDrawColor(c.r, c.g, c.b, c.a);
	interfaces->surface->drawLine(a.x, a.y, b.x, b.y);
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t* text, bool centered, color color) {
	interfaces->surface->setTextFont(font);
	int text_width, text_height;

	if (centered) {
		interfaces->surface->get_text_size(font, text, text_width, text_height);
		interfaces->surface->draw_text_pos(x - text_width / 2, y);
	}
	else
		interfaces->surface->draw_text_pos(x, y);

	interfaces->surface->setTextColor(color.r, color.g, color.b, color.a);
	interfaces->surface->draw_render_text(text, wcslen(text));
}

void render::circle(Vector center, color color, float r, float points)
{
	interfaces->surface->setDrawColor(color.r, color.g, color.b);
	for (int i = 0; i < r; i++)
		interfaces->surface->drawOutlinedCircle(center.x, center.y, i, points);
}

void render::Nigger(std::string preto)
{
 
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color) {
	wchar_t temp[128];
	int text_width, text_height;
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
		interfaces->surface->setTextFont(font);
		if (centered) {
			interfaces->surface->get_text_size(font, temp, text_width, text_height);
			interfaces->surface->draw_text_pos(x - text_width / 2, y);
		}
		else
			interfaces->surface->draw_text_pos(x, y);
		interfaces->surface->setTextColor(color.r, color.g, color.b, color.a);
		interfaces->surface->draw_render_text(temp, wcslen(temp));
	}
}

void render::draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces->surface->setDrawColor(color.r, color.g, color.b, color.a);
	interfaces->surface->drawOutlinedRect(x, y, width, height);
}

void render::draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces->surface->setDrawColor(color.r, color.g, color.b, color.a);
	interfaces->surface->drawFilledRect(x, y, width, height);
}

void render::draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces->surface->setDrawColor(color.r, color.g, color.b, color.a);
	interfaces->surface->drawOutlinedRect(x, y, width, height);
}

void render::draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color) {
	float step = M_PI * 2.0 / segments;
	for (float a = 0; a < (M_PI * 2.0); a += step) {
		float x1 = radius * cos(a) + x;
		float y1 = radius * sin(a) + y;
		float x2 = radius * cos(a + step) + x;
		float y2 = radius * sin(a + step) + y;
		interfaces->surface->setDrawColor(color.r, color.g, color.b, color.a);
		interfaces->surface->drawLine(x1, y1, x2, y2);
	}
}

Vector2 render::get_text_size(unsigned long font, std::string text) {
	std::wstring a(text.begin(), text.end());
	const wchar_t* wstr = a.c_str();
	static int w, h;

	interfaces->surface->get_text_size(font, wstr, w, h);
	return { static_cast<float>(w), static_cast<float>(h) };
}