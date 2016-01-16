#ifndef CELL_H
#define CELL_H


class Cell
{
public:
	static const int MINE = -1;

	// C'TORS AND D'TOR
	Cell(int value = 0);
	Cell(const Cell & copy);
	~Cell();

	// OPERATORS
	Cell & operator=(const Cell & rhs);

	// GETTERS AND SETTERS
	int Value() const;
	void SetValue(int value);

	bool Checked() const;
	void SetChecked(bool checked);

	bool Flagged() const;
	void SetFlagged(bool flagged);

private:
	int m_value;
	bool m_checked;
	bool m_flagged;

};


#endif // CELL_H
