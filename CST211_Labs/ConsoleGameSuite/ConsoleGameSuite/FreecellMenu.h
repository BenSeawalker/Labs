#ifndef FREECELLMENU_H
#define FREECELLMENU_H

#include "Menu.h"
#include "Freecell.h"

class FreecellMenu
{
public:
	enum BUTTON { PLAY, GAME, SCENARIOS, EXIT, VICTORY, STACKS, };
	FreecellMenu();
	FreecellMenu(const FreecellMenu & copy);

	~FreecellMenu();

	FreecellMenu & operator=(const FreecellMenu & rhs);

	bool Update();

private:
	Menu m_mainMenu;
	Freecell * m_game;
};

#endif // FREECELLMENU_H
