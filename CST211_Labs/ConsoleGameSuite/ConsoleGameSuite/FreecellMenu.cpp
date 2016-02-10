#include "FreecellMenu.h"

#include "Keyboard.h"

FreecellMenu::FreecellMenu()
	: m_mainMenu(0, CWidth() / 2, CHeight() / 4, Color::green), m_game(nullptr)
{
	Menu scenarios(0, 0, 0, Color::green);
	scenarios.AddButton(Button(0, 0, VICTORY, "Victory"));
	scenarios.AddButton(Button(0, 0, STACKS, "Stacks"));
	scenarios.AddButton(Button(0, 0, BACK_ID, "Back"));

	m_mainMenu.AddButton(Button(0, 0, PLAY, "Play"));
	m_mainMenu.AddButton(Button(0, 0, GAME, "Game"));
	m_mainMenu.AddSubmenu(Button(0, 0, SCENARIOS, "Scenarios"), scenarios);
	m_mainMenu.AddButton(Button(0, 0, EXIT, "Exit"));

	m_mainMenu.Draw();
}

FreecellMenu::FreecellMenu(const FreecellMenu & copy)
	: m_mainMenu(copy.m_mainMenu), m_game(copy.m_game)
{}

FreecellMenu::~FreecellMenu()
{}

FreecellMenu & FreecellMenu::operator=(const FreecellMenu & rhs)
{
	if (this != &rhs)
	{
		m_mainMenu = rhs.m_mainMenu;
		m_game = rhs.m_game;
	}

	return *this;
}

bool FreecellMenu::Update()
{
	bool running = true;

	if (m_game)
	{
		if (!m_game->Update())
		{
			Keyboard::ClearState();

			delete m_game;
			m_game = nullptr;

			m_mainMenu.Draw();
		}
	}
	else
	{
		m_mainMenu.Update();

		Button * b = m_mainMenu.Clicked(Mouse::LEFT);
		if (b)
		{
			switch (b->ID())
			{
			case PLAY:
				m_game = new Freecell;
				break;

			case GAME:
				
				break;

			case EXIT:
				running = false;
				break;

			case VICTORY:
				m_game = new Freecell(FCBoard::VICTORY);
				break;

			case STACKS:
				m_game = new Freecell(FCBoard::STACKS);
				break;
			}
		}
	}

	return (running && !Keyboard::KeyPressed(VK_ESCAPE));
}
