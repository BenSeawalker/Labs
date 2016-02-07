#ifndef CARDBTN_H
#define CARDBTN_H

#include "Card.h"
#include "Button.h"

class CardBtn : public Button
{
public:
	CardBtn();
	CardBtn(const Card & card);
	CardBtn(const CardBtn & copy);

	virtual ~CardBtn();

	CardBtn & operator=(const CardBtn & rhs);

	virtual void Draw();

	void Large(COLOR background = Color::green);
	void Small(COLOR background = Color::green);

private:
	const int SIZE = 9;

	int m_rank;
	string m_suit;
	COLOR m_color;
};

#endif // CARDBTN_H
