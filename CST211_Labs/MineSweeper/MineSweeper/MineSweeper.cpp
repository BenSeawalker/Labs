#include "MineSweeper.h"

Console & MineSweeper::console = Console::GetInstance();
const double MineSweeper::PI = (atan(1) * 4);

#define SMILE "\x01"
#define DEAD  "\x02"
#define HEART "\x03"

MineSweeper::MineSweeper()
	: m_menu(4), m_onMenu(true), m_paused(false), m_firstClick(true), m_clicks(0), m_mines(0), m_flags(0)
{
	// Main Menu
	m_menu[BEGINNER] = Button(40, 15, BEGINNER, "Easy");
	m_menu[INTERMEDIATE] = Button(40, 19, INTERMEDIATE, "Intermediate");
	m_menu[EXPERT] = Button(40, 23, EXPERT, "Hard");
	m_menu[3] = Button(40, 27, 3, "Quit");

	// Game Menu
	m_btnQuit = Button(OFFSET_X + 1, OFFSET_Y - 4, 0, "X", Color::dark_red, Color::white, Color::red, Color::bright_white);
	m_btnReset = Button(OFFSET_X + 8, OFFSET_Y - 4, 0, SMILE, Color::grey, Color::yellow, Color::white, Color::yellow);
	m_btnScore = Button(OFFSET_X + 15, OFFSET_Y - 4, 0, "Clicks: 0", Color::white, Color::blue, Color::white, Color::blue);

	// rename console window
	SetConsoleTitle(L"Mine Sweeper");

	// Set the Console to the appropriate size
	console.Resize(100, 50);

	ShowMenu();
}

MineSweeper::~MineSweeper()
{}


bool MineSweeper::Update()
{
	// If the game is active
	if (m_gameRunning)
	{
		// Update Game Menu:
		if (!m_onMenu)
		{
			m_btnQuit.Update();
			m_btnReset.Update();

			if (Keyboard::KeyPressed(int('R')) || m_btnReset.Clicked(Mouse::LEFT))
			{
				Cleanup();
				ShowGame();
			}

			// Check if user wants to return to menu
			if (Keyboard::KeyPressed(int('Q')) || m_btnQuit.Clicked(Mouse::LEFT))
			{
				Cleanup();
				ShowMenu();
			}
		}

		// Only update if there was a mouse event or it isn't paused...
		if (Mouse::Moved() || Mouse::BtnPressed(Mouse::LEFT) || Mouse::BtnPressed(Mouse::RIGHT))
		{
			if (m_onMenu)
			{
				// Update Main Menu
				for (int i = 0; i < m_menu.Length(); ++i)
				{
					m_menu[i].Update();

					if (m_menu[i].Clicked(Mouse::LEFT))
						MenuButtonClicked(m_menu[i]);
				}
			}
			else if (!m_paused)
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

	return m_gameRunning;
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


void MineSweeper::ShowGame()
{
	int columns, rows;

	m_paused = false;
	m_clicks = 0;
	m_flags = 0;

	switch (m_difficulty)
	{
	case BEGINNER:
		columns = 10;
		rows = 10;
		m_mines = 10;
		break;

	case INTERMEDIATE:
		columns = 16;
		rows = 16;
		m_mines = 40;
		break;

	case EXPERT:
		columns = 30;
		rows = 16;
		m_mines = 100;
		break;
	}

	m_cellButtons.Resize(rows, columns);
	m_board.Resize(rows, columns);
	m_mineCoords.SetLength(m_mines);

	console.Clear();

	// MENU BUTTONS
	m_btnQuit.Draw();
	m_btnReset.SetText(SMILE);
	m_btnReset.SetColors(Color::grey, Color::yellow, Color::white, Color::yellow);
	SetClicks(0);

	// CELL BUTTONS
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			m_cellButtons[y][x] = Button(x * CELL_WIDTH + OFFSET_X, y * CELL_HEIGHT + OFFSET_Y, 0, "", Color::white, 0, Color::cyan, 0);
			m_cellButtons[y][x].Resize(CELL_WIDTH, CELL_HEIGHT);
		}
	}
}

void MineSweeper::MenuButtonClicked(Button & btn)
{
	if (btn.ID() == 3)
	{
		m_gameRunning = false;
	}
	else
	{
		m_onMenu = false;
		m_difficulty = DIFFICULTY(btn.ID());
		ShowGame();
	}
}

void MineSweeper::CellButtonClicked(Button & btn)
{
	int x = (btn.X() - OFFSET_X) / CELL_WIDTH,
		y = (btn.Y() - OFFSET_Y) / CELL_HEIGHT;

	if (m_firstClick)
	{
		m_firstClick = false;
		SetClicks(++m_clicks);
		Populate(m_board.Rows(), m_board.Columns(), x, y);
	}
	else
	{
		if (!IsChecked(x, y) && !IsFlagged(x, y))
		{
			SetClicks(++m_clicks);
		}
	}

	UncoverCell(x, y);
	CheckVictory();
}

void MineSweeper::CellButtonRightClicked(Button & btn)
{
	int x = (btn.X() - OFFSET_X) / CELL_WIDTH,
		y = (btn.Y() - OFFSET_Y) / CELL_HEIGHT;

	FlagCell(x, y);
	CheckVictory();
}

void MineSweeper::SetClicks(int clicks)
{
	m_clicks = clicks;
	string txt = string("Clicks: ").append(to_string(m_clicks));
	m_btnScore.SetText(txt);
}

void MineSweeper::Populate(int rows, int columns, int fc_x, int fc_y)
{
	// Place mines
	srand((unsigned)time(NULL));
	for (int i = 0; i < m_mines; ++i)
	{
		int x = rand() % (columns);
		int y = rand() % (rows);

		while (((x == fc_x) && (y == fc_y)) || m_board[y][x].Value() == Cell::MINE)
		{
			x = rand() % (columns);
			y = rand() % (rows);
		}

		m_mineCoords[i] = { x, y };
		m_board[y][x].SetValue(Cell::MINE);
	}

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			m_board[y][x].SetValue(CalcCellValue(x, y));
		}
	}
	
}

int MineSweeper::CalcCellValue(int x, int y)
{
	int value = Cell::MINE;

	if (m_board[y][x].Value() != Cell::MINE)
	{
		value = 0;

		// Check the surrounding cells in the 8 cardinal directions
		for (int i = 0; i < 8; ++i)
		{
			int dx = x + round(cos((PI / 4) * i));
			int dy = y + round(sin((PI / 4) * i));

			if (m_board.Contains(dy, dx))
				value += IsMine(dx, dy);
		}
	}

	return value;
}

bool MineSweeper::IsMine(int x, int y)
{
	return (m_board[y][x].Value() == Cell::MINE);
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
	// Uncover this cell
	if (m_board.Contains(y, x) && !IsChecked(x, y) && !IsFlagged(x, y))
	{
		if (IsMine(x, y))
		{
			// You lose...
			LoseGame(x, y);
		}
		else
		{
			// CELL
			m_board[y][x].SetChecked(true);

			// BUTTON
			m_cellButtons[y][x].SetColors(Color::grey, Color::blue, Color::grey, Color::blue);
			
			int value = m_board[y][x].Value();
			if (value != 0)
			{
				if (value == 2)
					m_cellButtons[y][x].SetColors(Color::grey, Color::green, Color::grey, Color::green);
				else if (value == 3)
					m_cellButtons[y][x].SetColors(Color::grey, Color::dark_red, Color::grey, Color::dark_red);
				else if (value == 4)
					m_cellButtons[y][x].SetColors(Color::grey, Color::dark_blue, Color::grey, Color::dark_blue);
				else if (value == 5)
					m_cellButtons[y][x].SetColors(Color::grey, Color::purple, Color::grey, Color::purple);
				else if (value == 6)
					m_cellButtons[y][x].SetColors(Color::grey, Color::turquoise, Color::grey, Color::turquoise);
				else if (value == 7)
					m_cellButtons[y][x].SetColors(Color::grey, Color::lime, Color::grey, Color::lime);
				else if (value == 8)
					m_cellButtons[y][x].SetColors(Color::grey, Color::red, Color::grey, Color::red);

				m_cellButtons[y][x].SetText(to_string(value));
				m_cellButtons[y][x].Resize(CELL_WIDTH, CELL_HEIGHT);
			}
		}
	}

	// Uncover surrounding areas
	if (IsEmpty(x, y) && !IsFlagged(x, y))
	{
		// Uncover the surrounding cells in the 8 cardinal directions
		for (int i = 0; i < 8; ++i)
		{
			int dx = x + round(cos((PI / 4) * i));
			int dy = y + round(sin((PI / 4) * i));
			
			if (m_board.Contains(dy, dx) && !IsMine(dx, dy) && !IsChecked(dx, dy))
				UncoverCell(dx, dy);
		}
	}
}

void MineSweeper::FlagCell(int x, int y)
{
	if (!IsChecked(x, y))
	{
		m_board[y][x].SetFlagged(!IsFlagged(x, y));

		SetClicks(++m_clicks);

		if (IsFlagged(x, y))
		{
			m_flags++;
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::dark_red, Color::red);
			m_cellButtons[y][x].SetText("P", false);
		}
		else
		{
			m_flags--;
			m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::cyan, Color::red);
			m_cellButtons[y][x].SetText("", false);
		}
	}
}

void MineSweeper::CheckVictory()
{
	bool winning = false;

	// If you haven't placed more flags than mines
	if (m_flags <= m_mines)
	{
		// Check if all bombs have been flagged
		if (m_flags == m_mines)
		{
			winning = true;

			for (int i = 0; i < m_mineCoords.Length(); ++i)
			{
				if (!IsFlagged(m_mineCoords[i].X, m_mineCoords[i].Y))
					winning = false;
			}
		}

		// If the mines aren't all flagged 
		if (!winning)
		{
			winning = true;

			// Check if all squares have been uncovered
			for (int y = 0; y < m_board.Rows() && winning; ++y)
			{
				for (int x = 0; x < m_board.Columns(); x++)
				{
					// If its not a mine and it hasn't been uncovered yet....
					if (!IsMine(x, y) && !IsChecked(x, y))
						winning = false;
				}
			}
		}
	}

	if (winning)
		WinGame();
}

void MineSweeper::WinGame()
{
	// Flag all the mines
	for (int y = 0; y < m_board.Rows(); ++y)
	{
		for (int x = 0; x < m_board.Columns(); x++)
		{
			if (IsMine(x, y))
			{
				if (IsFlagged(x, y))
				{
					m_cellButtons[y][x].SetColors(Color::green, Color::red, Color::green, Color::red);
				}
				else
				{
					m_cellButtons[y][x].SetColors(Color::white, Color::red, Color::white, Color::red);
					m_cellButtons[y][x].SetText("P", false);
				}
			}
		}
	}

	// Update the game menu
	m_btnReset.SetText(HEART);
	m_btnReset.SetColors(Color::grey, Color::pink, Color::white, Color::pink);

	// Write the Winning Message
	int line = ((m_cellButtons.Rows() * CELL_HEIGHT) + OFFSET_Y + 1);
	console.ClearLine(line);
	console.ClearLine(line + 1);
	console.Write({ 5, line }, "Survival!", MakeColor(Color::lime, Color::black));
	console.Write({ 5, line + 1 }, "Press \"Q\" to return to Menu, \"R\" to Restart, or \"Esc\" to Exit...");

	m_paused = true;
}

void MineSweeper::LoseGame(int mine_x, int mine_y)
{
	// find all the mines
	for (int y = 0; y < m_board.Rows(); ++y)
	{
		for (int x = 0; x < m_board.Columns(); ++x)
		{
			if (IsMine(x, y))
			{
				if (IsFlagged(x, y))
				{
					m_cellButtons[y][x].SetColors(Color::dark_red, Color::red, Color::dark_red, Color::red);
				}
				else
				{
					m_cellButtons[y][x].SetColors(Color::grey, Color::black, Color::grey, Color::black);
					m_cellButtons[y][x].SetText("*", false);
				}
			}
		}
	}

	// Mark the losing mine
	m_cellButtons[mine_y][mine_x].SetColors(Color::red, Color::black, Color::red, Color::black);

	// Update the game menu
	m_btnReset.SetText(DEAD);
	m_btnReset.SetColors(Color::grey, Color::black, Color::white, Color::black);

	// Write the Losing Message
	int line = ((m_cellButtons.Rows() * CELL_HEIGHT) + OFFSET_Y + 1);
	console.ClearLine(line);
	console.ClearLine(line + 1);
	console.Write({ 5, line }, "Violent death! (And probable loss of limb)", MakeColor(Color::red, Color::black));
	console.Write({ 5, line + 1 }, "Press \"Q\" to return to Menu, \"R\" to Restart, or \"Esc\" to Exit...");
	
	m_paused = true;
}

void MineSweeper::Cleanup()
{
	SetClicks(0);
	m_firstClick = true;
	m_mines = 0;
	m_flags = 0;

	m_board.Purge();
	m_cellButtons.Purge();
	m_mineCoords.Purge();
}

