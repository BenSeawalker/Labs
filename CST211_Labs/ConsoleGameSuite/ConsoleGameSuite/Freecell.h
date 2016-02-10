#ifndef FREECELL_H
#define FREECELL_H


#include "View.h"

#include "FCBoard.h"
#include "Array.h"
#include "CardBtn.h"

#define FREE_CELLS 4
#define HOME_CELLS 4
#define PLAY_CELLS 8

class Freecell : public View
{
public:
	static const int OFF_X = CardBtn::SIZE;
	static const int OFF_Y = 3;
	static const int TOTAL_CARDS = 68; // to hold all 52 CardBtns + 16 empty cards

	Freecell();
	Freecell(FCBoard::SCENARIO scenario);
	Freecell(const Freecell & copy);

	virtual ~Freecell();

	Freecell & operator=(const Freecell & rhs);

	bool Update();

protected:
	virtual void ModelUpdated();

private:
	void Draw();

	void DrawFreeArea();
	void DrawHomeArea();
	void DrawPlayArea();

	void DeselectAll();

	void CheckVictory();
	void WinGame();

	bool m_running;
	bool m_paused;
	Array<CardBtn> m_cards;
	FCBoard m_board;

	CardBtn * m_selected;
	bool m_moved;
};

#endif // FREECELL_H
