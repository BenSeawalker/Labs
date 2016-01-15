#ifndef BUTTON_H
#define BUTTON_H

#include <string>
using std::string;

#include "Console.h"
#include "Mouse.h"

class Button
{
public:
	Button(int x, int y, int id, const string & text, void(*clicked)(Button &) = nullptr, COLOR background = Color::white, COLOR foreground = Color::black,
								COLOR background_hover = Color::bright_white, COLOR foreground_hover = Color::grey);
	~Button();

	// METHODS
	void Update();
	void Draw();

	// GETTERS AND SETTERS
	int ID() const;
	const string & Text() const;

	void Resize(int width, int height, COLOR background = Color::black);

private:
	// MEMBERS
	void(*Clicked)(Button &);

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
