#include "MineSweeper.h"

Console & MineSweeper::console = Console::GetInstance();

MineSweeper::MineSweeper()
	: m_menu(3), m_onMenu(true)
{
	m_menu[BEGINNER] = Button(40, 15, BEGINNER, "Easy");
	m_menu[INTERMEDIATE] = Button(40, 19, INTERMEDIATE, "Intermediate");
	m_menu[EXPERT] = Button(40, 23, EXPERT, "Hard");

	console.Resize(100, 64);

	ShowMenu();
}

MineSweeper::~MineSweeper()
{}


void MineSweeper::Update()
{
	// Check if user wants to return to menu
	if (Keyboard::KeyPressed(int('Q')))
	{
		m_board.Purge();
		m_cellButtons.Purge();

		ShowMenu();
	}

	// Only update if there was a mouse event...
	if (Mouse::Moved() || Mouse::BtnPressed(Mouse::LEFT) || Mouse::BtnPressed(Mouse::RIGHT))
	{
		if (m_onMenu)
		{
			// Update the menu
			for (int i = 0; i < m_menu.Length(); ++i)
			{
				m_menu[i].Update();

				if (m_menu[i].Clicked(Mouse::LEFT))
					MenuButtonClicked(m_menu[i]);
			}
		}
		else
		{
			// Update the game
			for (int y = 0; y < m_cellButtons.Rows(); ++y)
			{
				for (int x = 0; x < m_cellButtons.Columns(); ++x)
				{
					m_cellButtons[y][x].Update();

					// Handle left click
					if (m_cellButtons[y][x].Clicked(Mouse::LEFT))
						CellButtonClicked(m_cellButtons[y][x]);

					// Handle right click
					if (m_cellButtons[y][x].Clicked(Mouse::RIGHT))
						CellButtonRightClicked(m_cellButtons[y][x]);
				}
			}
		}
	}
}


void MineSweeper::ShowMenu()
{
	m_onMenu = true;

	console.Clear();

	string border_h = string(console.Width() * 3 / 4, '=');

	console.Write({ console.Width() / 8, console.Height() / 4 }, border_h.c_str());
	console.Write({ console.Width() / 8, console.Height() * 3 / 4 }, border_h.c_str());

	for (int i = 0; i < m_menu.Length(); ++i)
		m_menu[i].Draw();
}


void MineSweeper::Initialize(DIFFICULTY difficulty)
{
	int columns, rows, mines;

	switch (difficulty)
	{
	case BEGINNER:
		columns = 10;
		rows = 10;
		mines = 10;
		break;

	case INTERMEDIATE:
		columns = 16;
		rows = 16;
		mines = 40;
		break;

	case EXPERT:
		columns = 30;
		rows = 16;
		mines = 100;
		break;
	}

	m_cellButtons.Resize(rows, columns);
	m_board.Resize(rows, columns);
	console.Clear();

	srand((unsigned)time(NULL));
	for (int i = 0; i < mines; ++i)
	{
		int x = rand() % (columns - 1);
		int y = rand() % (rows - 1);

		while (m_board[y][x].Value() == Cell::MINE)
		{
			x = rand() % (columns - 1);
			y = rand() % (rows - 1);
		}

		m_board[y][x].SetValue(Cell::MINE);
	}

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			// CELLS
			m_board[y][x].SetValue(CalcCellValue(x, y));

			// BUTTONS
			m_cellButtons[y][x] = Button(x * BUTTON_WIDTH, y * BUTTON_HEIGHT, 0, "", Color::white, Color::red, Color::cyan, Color::red);
			m_cellButtons[y][x].Resize(BUTTON_WIDTH, BUTTON_HEIGHT);
		}
	}
}

void MineSweeper::MenuButtonClicked(Button & btn)
{
	m_onMenu = false;
	Initialize(DIFFICULTY(btn.ID()));
}

void MineSweeper::CellButtonClicked(Button & btn)
{
	UncoverCell(btn.X() / BUTTON_WIDTH, btn.Y() / BUTTON_HEIGHT);
}

void MineSweeper::CellButtonRightClicked(Button & btn)
{
	FlagCell(btn.X() / BUTTON_WIDTH, btn.Y() / BUTTON_HEIGHT);
}

int MineSweeper::CalcCellValue(int x, int y)
{
	int value = Cell::MINE;

	if (m_board[y][x].Value() != Cell::MINE)
	{
		// NORTH
		value = IsMine(x, y - 1);

		// NORTH EAST
		value += IsMine(x + 1, y - 1);

		// EAST
		value += IsMine(x + 1, y);

		// SOUTH EAST
		value += IsMine(x + 1, y + 1);

		// SOUTH
		value += IsMine(x, y + 1);

		// SOUTH WEST
		value += IsMine(x - 1, y + 1);

		// WEST
		value += IsMine(x - 1, y);

		// NORTH WEST
		value += IsMine(x - 1, y - 1);
	}

	return value;
}

bool MineSweeper::IsMine(int x, int y)
{
	return (m_board.Contains(y, x) && m_board[y][x].Value() == Cell::MINE);
}

bool MineSweeper::IsChecked(int x, int y)
{
	return m_board[y][x].Checked();
}

bool MineSweeper::IsEmpty(int x, int y)
{
	return (m_board[y][x].Value() == 0);
}

bool MineSweeper::IsFlagged(int x, int y)
{
	return (m_board[y][x].Flagged() == true);
}

void MineSweeper::UncoverCell(int x, int y)
{
	/*int temp = x;
	x = y;
	y = temp;*/

	// Uncover this cell
	if (m_board.Contains(y, x) && !IsChecked(x, y) && !IsMine(x, y) && !IsFlagged(x, y))
	{
		if (!IsMine(x, y))
		{
			// CELL
			m_board[y][x].SetChecked(true);

			m_cellButtons[y][x].SetColors(Color::grey, Color::blue, Color::grey, Color::blue);

			// BUTTON
			int value = m_board[y][x].Value();
			if (value != 0)
			{
				if (value == 2)
					m_cellButtons[y][x].SetColors(Color::grey, Color::green, Color::grey, Color::green);
				else if (value == 3)
					m_cellButtons[y][x].SetColors(Color::grey, Color::dark_red, Color::grey, Color::dark_red);
				else if (value == 4)
					m_cellButtons[y][x].SetColors(Color::grey, Color::dark_blue, Color::grey, Color::dark_blue);
				else if (value > 4)
					m_cellButtons[y][x].SetColors(Color::grey, Color::red, Color::grey, Color::red);

				m_cellButtons[y][x].SetText(to_string(value));
				m_cellButtons[y][x].Resize(BUTTON_WIDTH, BUTTON_HEIGHT);
			}
		}
	}

	// Uncover surrounding areas
	if (IsEmpty(x, y) && !IsFlagged(x, y))
	{
		// NORTH
		if (m_board.Contains(y - 1, x) && !IsMine(x, y - 1) && !IsChecked(x, y - 1))
			UncoverCell(x, y - 1);

		// EAST
		if (m_board.Contains(y, x + 1) && !IsMine(x + 1, y) && !IsChecked(x + 1, y))
			UncoverCell(x + 1, y);

		// SOUTH
		if (m_board.Contains(y + 1, x) && !IsMine(x, y + 1) && !IsChecked(x, y + 1))
			UncoverCell(x, y + 1);

		// WEST
		if (m_board.Contains(y, x - 1) && !IsMine(x - 1, y) && !IsChecked(x - 1, y))
			UncoverCell(x - 1, y);
	}
}

void MineSweeper::FlagCell(int x, int y)
{
	if (!IsChecked(x, y))
	{
		m_board[y][x].SetFlagged(!IsFlagged(x, y));

		if (IsFlagged(x, y))
		{
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::dark_red, Color::red);
			m_cellButtons[y][x].SetText("!", false);
		}
		else
		{
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::cyan, Color::red);
			m_cellButtons[y][x].SetText("", false);
		}
	}
}

