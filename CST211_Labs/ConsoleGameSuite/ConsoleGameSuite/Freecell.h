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

	Freecell();
	Freecell(FCBoard * model);
	virtual ~Freecell();

	bool Update();

protected:
	virtual void ModelUpdated();

private:
	void Draw();

	void DrawFreeArea();
	void DrawHomeArea();
	void DrawPlayArea();

	void DeselectAll();

	bool m_running;
	Array<CardBtn> m_cards;

	CardBtn * m_selected;
};

#endif // FREECELL_H
