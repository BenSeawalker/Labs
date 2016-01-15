#include "Button.h"


Button::Button(int x, int y, int id, const string & text, void(*clicked)(Button &), COLOR background, COLOR foreground, COLOR background_hover, COLOR foreground_hover)
	: m_x(x), m_y(y), m_id(id), m_text(text),
	m_background(background), m_foreground(foreground), m_backgroundHover(background_hover), m_foregroundHover(foreground_hover),
	m_hover(false), m_height(3)
{
	m_width = m_text.length() + 2;

	Clicked = clicked;

	Draw();
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
*		Modifies:	N/A
*		Throws:		N/A
*		Returns:	N/A
*************************************************************************/
void Button::Update()
{
	int mx = Mouse::X(),
		my = Mouse::Y();

	bool hover = ((mx >= m_x && mx < m_x + m_width) && (my >= m_y && my < m_y + m_height));
	
	if (Clicked != nullptr && hover && Mouse::BtnPressed(Mouse::LEFT))
		Clicked(*this);

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

const string & Button::Text() const
{
	return m_text;
}

void Button::Resize(int width, int height, COLOR background)
{
	(Console::GetInstance()).ClearRect(m_x, m_y, m_x + m_width, m_y + m_height, MakeBackground(background));

	m_width = width;
	m_height = height;

	Draw();
}

void Button::Draw()
{
	Console & console = Console::GetInstance();
	COLOR foreground = (m_hover ? m_foregroundHover : m_foreground);
	COLOR background = (m_hover ? m_backgroundHover : m_background);

	console.ClearRect(m_x, m_y, m_x + m_width, m_y + m_height, MakeBackground(background));

	char * str = new char[m_text.length() + 1];
	strcpy(str, m_text.c_str());

	if (m_text.length() >= m_width - 2)
	{
		delete[] str;
		str = new char[m_width - 1];
		for (int i = 0; i < m_width - 1; ++i)
			str[i] = m_text.c_str()[i];

		str[max(0, m_width - 2)] = '\0';
	}

	console.Write({ m_x + m_width/2 - strlen(str)/2, m_y + m_height/2 }, str, MakeColor(foreground, background));

	delete[] str;
}
