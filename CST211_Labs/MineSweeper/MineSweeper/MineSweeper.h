#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <time.h>
#include <string>
using std::string;
using std::to_string;

#include "Console.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Button.h"

#include "Board.h"


class MineSweeper
{
public:
	MineSweeper();
	~MineSweeper();

	bool Update();

private:
	// ENUMS, CONSTANTS, AND STATICS
	enum DIFFICULTY { BEGINNER, INTERMEDIATE, EXPERT };

	static const double PI;

	static const int CELL_WIDTH = 3;
	static const int CELL_HEIGHT = 2;
	static const int OFFSET_X = 6;
	static const int OFFSET_Y = 10;

	static Console & console;

	//	METHODS
	void ShowMenu();
	void ShowGame();

	void MenuButtonClicked(Button & btn);
	void CellButtonClicked(Button & btn);
	void CellButtonRightClicked(Button & btn);

	void SetClicks(int clicks);

	void Populate(int rows, int columns, int fc_x, int fc_y);

	int CalcCellValue(int x, int y);
	bool IsMine(int x, int y);
	bool IsChecked(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsFlagged(int x, int y);

	void UncoverCell(int x, int y);
	void FlagCell(int x, int y);

	void CheckVictory();
	void WinGame();
	void LoseGame(int mine_x, int mine_y);

	void Cleanup();

	// MEMBERS
	Board m_board;
	Array2D<Button> m_cellButtons;
	Array<COORD> m_mineCoords;

	Array<Button> m_menu;
	Button m_btnQuit;
	Button m_btnReset;
	Button m_btnScore;

	bool m_onMenu;
	bool m_paused;
	bool m_gameRunning;

	DIFFICULTY m_difficulty;
	bool m_firstClick = false;
	int m_clicks;
	int m_mines;
	int m_flags;
};


#endif // MINESWEEPER_H
