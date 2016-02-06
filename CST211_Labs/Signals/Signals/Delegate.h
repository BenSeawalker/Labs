#ifndef DELEGATE_H
#define DELEGATE_H

template<typename OT, typename FT>
class Delegate
{
public:
	Delegate(OT * owner, FT * func)
		: m_owner(owner), m_func(func)
	{}

	void operator()()
	{
		if (m_owner)
			m_owner->(*m_func)();
		else
			(*m_func)();
	}

private:
	OT * m_owner;
	FT * m_func;
};


template<typename OT, typename FT, typename PT>
class Delegate
{
public:
	Delegate(OT * owner, FT * func, PT & param)
		: m_owner(owner), m_func(func), m_param(param)
	{}

	void operator()()
	{
		if (m_owner)
			m_owner->(*m_func)(m_param);
		else
			(*m_func)(m_param);
	}

private:
	OT * m_owner;
	FT * m_func;
	PT & m_param;
};

#endif // DELEGATE_H