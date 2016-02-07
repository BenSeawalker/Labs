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

	bool m_running;
	Array<CardBtn> m_cards;
};

#endif // FREECELL_H
