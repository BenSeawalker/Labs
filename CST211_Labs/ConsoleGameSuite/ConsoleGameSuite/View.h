#ifndef VIEW_H
#define VIEW_H

class View
{
	friend class Model;

protected:
	View(Model * model = nullptr);

	virtual void ModelUpdated() = 0;

private:
	Model * m_model;
};

#endif // VIEW_H
