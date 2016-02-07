#include "CardBtn.h"


CardBtn::CardBtn()
	: m_rank(NONE), m_suit(""), m_color(Color::grey)
{
	Small();
	SetColors(Color::white, m_color, Color::bright_white, m_color);
	SetText(m_suit, false);
}

CardBtn::CardBtn(const Card & card)
	: m_rank(NONE), m_suit(""), m_color(Color::grey)
{

	m_rank = card.Rank();
	m_suit = card.Suit();
	m_color = ((card.Suit() <= DIAMONDS) ? Color::dark_red : Color::blue);

	Small();
	SetColors(Color::white, m_color, Color::bright_white, m_color);
	SetText(m_suit, false);
}

CardBtn::CardBtn(const CardBtn & copy)
	: Button(copy), m_rank(copy.m_rank), m_suit(copy.m_suit), m_color(copy.m_color)
{
	SetColors(Color::white, m_color, Color::bright_white, m_color);
	SetText(m_suit, false);
}

CardBtn::~CardBtn()
{}

CardBtn & CardBtn::operator=(const CardBtn & rhs)
{
	if (this != &rhs)
		Button::operator=(rhs);

	return *this;
}

void CardBtn::Draw()
{
	if (m_rank != NONE)
	{
		Button::Draw();

		string rank;
		switch (m_rank)
		{
		case KING:
			rank = "K";
			break;

		case QUEEN:
			rank = "Q";
			break;

		case JACK:
			rank = "J";
			break;

		case ACE:
			rank = "A";
			break;

		default:
			rank = std::to_string(m_rank);
			break;
		}

		COLOR back = (m_hover ? m_backgroundHover : m_background);

		// Small card
		if (m_height == 2)
		{
			// Horizontal line
			for (int x = m_x + 1; x < m_x + m_width - 1; ++x)
				CWrite(x, m_y, char(196), CMakeColor(m_color, back));

			// Vertical lines
			CWrite(m_x, m_y + 1, char(179), CMakeColor(m_color, back));
			CWrite(m_x + m_width - 1, m_y + 1, char(179), CMakeColor(m_color, back));

			// Corners
			CWrite(m_x, m_y, char(218), CMakeColor(m_color, back));
			CWrite(m_x + m_width - 1, m_y, char(191), CMakeColor(m_color, back));

			// Ranks and Suit
			CWrite(m_x + 1, m_y + 1, rank.c_str(), CMakeColor(m_color, back));
			//CWrite(m_x + m_width - 1 - (m_rank == 10), m_y, rank.c_str(), CMakeColor(m_color, back));
			//CWrite(m_x + m_width / 2, m_y, m_suit.c_str(), CMakeColor(m_color, back));
		}

		// Large card
		else
		{
			// Horizontal lines
			for (int x = m_x + 1; x < m_x + m_width - 1; ++x)
			{
				CWrite(x, m_y, char(196), CMakeColor(m_color, back));
				CWrite(x, m_y + m_height - 1, char(196), CMakeColor(m_color, back));
			}

			// Vertical lines
			for (int y = m_y + 1; y < m_y + m_height - 1; ++y)
			{
				CWrite(m_x, y, char(179), CMakeColor(m_color, back));
				CWrite(m_x + m_width - 1, y, char(179), CMakeColor(m_color, back));
			}

			// Corners
			CWrite(m_x, m_y, char(218), CMakeColor(m_color, back));
			CWrite(m_x + m_width - 1, m_y, char(191), CMakeColor(m_color, back));
			CWrite(m_x + m_width - 1, m_y + m_height - 1, char(217), CMakeColor(m_color, back));
			CWrite(m_x, m_y + m_height - 1, char(192), CMakeColor(m_color, back));

			// Rank
			CWrite(m_x + 1, m_y + 1, rank.c_str(), CMakeColor(m_color, back));
			CWrite(m_x + m_width - 2 - (m_rank == 10), m_y + m_height - 2, rank.c_str(), CMakeColor(m_color, back));
		}
	}
}

void CardBtn::Large(COLOR background)
{
	Resize(SIZE, SIZE, background);
}

void CardBtn::Small(COLOR background)
{
	Resize(SIZE, 2, background);
}
