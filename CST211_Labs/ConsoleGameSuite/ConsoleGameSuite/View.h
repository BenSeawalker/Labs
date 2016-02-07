#ifndef VIEW_H
#define VIEW_H

class View
{
	friend class Model; // to access ModelUpdated()

public:
	void SetModel(Model * model);
	Model * GetModel();
	const Model * GetModel() const;

protected:
	View(Model * model = nullptr);
	View(const View & copy);

	virtual ~View();

	View & operator=(const View & rhs);

	virtual void ModelUpdated() = 0;

private:
	Model * m_model;
};

#endif // VIEW_H
