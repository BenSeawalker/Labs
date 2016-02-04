#ifndef CARD_H
#define CARD_H

#define HEARTS	 char(3)
#define DIAMONDS char(4)
#define CLUBS	 char(5)
#define SPADES	 char(6)

#define KING  13
#define QUEEN 12
#define JACK  11
#define ACE	  1

class Card
{
public:
	Card(char suit = HEARTS, int rank = 1);
	Card(const Card & copy);

	~Card();

	Card & operator=(const Card & rhs);


	int Rank() const;
	char Suit() const;

private:
	char m_suit;
	int m_rank;
};

#endif // CARD_H
