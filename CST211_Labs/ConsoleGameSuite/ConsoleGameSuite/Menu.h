#ifndef MENU_H
#define MENU_H

#include <string>
using std::string;

#include "Array.h"
#include "Button.h"
#include "Console.h"

#define BACK_ID -1

class Menu
{
public:
	Menu(int id = 0, int x = 0, int y = 0, COLOR background = Color::black);
	Menu(const Menu & copy);

	~Menu();

	Menu & operator=(const Menu & rhs);

	void AddButton(Button button);
	void AddSubmenu(Button button, Menu sub);

	void SetPos(int x, int y);

	Button * Clicked(Mouse::BUTTON btn);

	void Update();
	void Draw();

private:
	void ResizeButtons();

	Array<Button> m_buttons;
	Array<Menu> m_submenus;

	Menu * m_current;
	Menu * m_previous;

	COLOR m_background;

	int m_id;
	int m_x;
	int m_y;
};

#endif // MENU_H
