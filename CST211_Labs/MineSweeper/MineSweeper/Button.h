#ifndef BUTTON_H
#define BUTTON_H

#include <string>
using std::string;

#include "Console.h"
#include "Mouse.h"

class Button
{
public:
	//Button(int x = 0, int y = 0, int id = 0, const string & text = "", void(*clicked)(Button &) = nullptr,
	//	COLOR background = Color::white, COLOR foreground = Color::black,
	//	COLOR background_hover = Color::bright_white, COLOR foreground_hover = Color::grey);

	Button(int x = 0, int y = 0, int id = 0, const string & text = "",
		COLOR background = Color::white, COLOR foreground = Color::black,
		COLOR background_hover = Color::bright_white, COLOR foreground_hover = Color::grey);

	~Button();

	// METHODS
	void Update();
	void Draw();

	void SetColors(COLOR background = Color::white, COLOR foreground = Color::black,
		COLOR background_hover = Color::bright_white, COLOR foreground_hover = Color::grey);

	// GETTERS AND SETTERS
	int ID() const;

	int X() const;
	int Y() const;

	bool Clicked(Mouse::BUTTON btn) const;

	const string & Text() const;
	void SetText(const string & text, bool resize = true);

	void Resize(int width, int height, COLOR background = Color::black);

private:
	// METHODS
	char * TrimText();

	// MEMBERS
	/*void(*Clicked)(void *, Button &);
	void * m_object;*/

	Array<bool> m_clicked;

	int m_id;
	string m_text;
	COLOR m_background;
	COLOR m_backgroundHover;
	COLOR m_foreground;
	COLOR m_foregroundHover;

	int m_x;
	int m_y;
	int m_width;
	int m_height;

	bool m_hover;
};

#endif // BUTTON_H
