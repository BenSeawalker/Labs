#include "Button.h"


//Button::Button(int x, int y, int id, const string & text, void(*clicked)(Button &), COLOR background, COLOR foreground, COLOR background_hover, COLOR foreground_hover)
//	: m_x(x), m_y(y), m_id(id), m_text(text),
//	m_background(background), m_foreground(foreground), m_backgroundHover(background_hover), m_foregroundHover(foreground_hover),
//	m_hover(false), m_height(3)
//{
//	m_width = m_text.length() + 2;
//
//	Clicked = clicked;
//}

Button::Button(int x, int y, int id, const string & text, COLOR background, COLOR foreground, COLOR background_hover, COLOR foreground_hover)
	: m_x(x), m_y(y), m_id(id), m_text(text),
	m_background(background), m_foreground(foreground), m_backgroundHover(background_hover), m_foregroundHover(foreground_hover),
	m_hover(false), m_clicked(3), m_height(3)
{
	m_width = m_text.length() + 2;

	m_clicked[Mouse::LEFT] = false;
	m_clicked[Mouse::MIDDLE] = false;
	m_clicked[Mouse::RIGHT] = false;
}

Button::~Button()
{}


/************************************************************************
* Purpose: To detect hover / click events on this button
*
* Precondition:
*		Assumes that Mouse::UpdateMouseState() has already been called
*
* Postcondition:
*		Modifies:	Console screen buffer
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::Update()
{
	int mx = Mouse::X(),
		my = Mouse::Y();

	bool hover = ((mx >= m_x && mx < m_x + m_width) && (my >= m_y && my < m_y + m_height));
	
	/*if (Clicked != nullptr && hover && Mouse::BtnPressed(Mouse::LEFT))
		Clicked(m_object, *this);*/

	m_clicked[Mouse::LEFT] = (hover && Mouse::BtnPressed(Mouse::LEFT));
	m_clicked[Mouse::MIDDLE] = (hover && Mouse::BtnPressed(Mouse::MIDDLE));
	m_clicked[Mouse::RIGHT] = (hover && Mouse::BtnPressed(Mouse::RIGHT));

	if (m_hover != hover)
	{
		m_hover = hover;
		Draw();
	}
}

int Button::ID() const
{
	return m_id;
}

int Button::X() const
{
	return m_x;
}

int Button::Y() const
{
	return m_y;
}

bool Button::Clicked(Mouse::BUTTON btn) const
{
	return m_clicked[btn];
}

const string & Button::Text() const
{
	return m_text;
}

void Button::SetText(const string & text, bool resize)
{
	m_text = text;

	if (resize)
		m_width = m_text.length() + 2;

	Draw();
}

void Button::Resize(int width, int height, COLOR background)
{
	if (width < m_width || height < m_height)
		(Console::GetInstance()).ClearRect(m_x, m_y, m_x + m_width, m_y + m_height, MakeBackground(background));

	m_width = width;
	m_height = height;

	Draw();
}

char * Button::TrimText()
{
	char * str = nullptr;

	if (int(m_text.length()) >= m_width - (2 * (m_width > 2)))
	{
		str = new char[m_width - 1];
		for (int i = 0; i < m_width - 1; ++i)
			str[i] = m_text.c_str()[i];

		str[max(0, m_width - 2)] = '\0';
	}
	else
	{
		str = new char[m_text.length() + 1];
		strcpy(str, m_text.c_str());
	}

	return str;
}

void Button::Draw()
{
	Console & console = Console::GetInstance();
	COLOR foreground = (m_hover ? m_foregroundHover : m_foreground);
	COLOR background = (m_hover ? m_backgroundHover : m_background);

	console.ClearRect(m_x, m_y, m_x + m_width, m_y + m_height, MakeBackground(background));

	char * str = TrimText();
	console.Write({ m_x + m_width/2 - strlen(str)/2, m_y + m_height/2 }, str, MakeColor(foreground, background));

	delete[] str;
}

void Button::SetColors(COLOR background, COLOR foreground, COLOR background_hover, COLOR foreground_hover)
{
	m_background = background;
	m_foreground = foreground;
	
	m_backgroundHover = background_hover;
	m_foregroundHover = foreground_hover;

	Draw();
}
