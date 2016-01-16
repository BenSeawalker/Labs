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

	void Update();

private:
	// ENUMS, CONSTANTS, AND STATICS
	enum DIFFICULTY { BEGINNER, INTERMEDIATE, EXPERT };
	static const int CELL_WIDTH = 3;
	static const int CELL_HEIGHT = 2;
	static Console & console;

	//	METHODS
	void ShowMenu();

	void Initialize(DIFFICULTY difficulty);

	void MenuButtonClicked(Button & btn);
	void CellButtonClicked(Button & btn);
	void CellButtonRightClicked(Button & btn);

	int CalcCellValue(int x, int y);
	bool IsMine(int x, int y);
	bool IsChecked(int x, int y);
	bool IsEmpty(int x, int y);
	bool IsFlagged(int x, int y);

	void UncoverCell(int x, int y);
	void FlagCell(int x, int y);

	// MEMBERS
	Board m_board;
	Array2D<Button> m_cellButtons;

	Array<Button> m_menu;

	bool m_onMenu;
};


#endif // MINESWEEPER_H
