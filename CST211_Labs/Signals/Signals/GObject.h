#ifndef GOBJECT_H
#define GOBJECT_H

#define SIGNAL()

class GObject
{
public:
	GObject();
	virtual ~GObject();

protected:
	template<typename F1, typename F2>
	void Connect(GObject * g1, F1 signal, GObject * g2, F2 slot);
};

template<typename F1, typename F2>
void GObject::Connect(GObject * g1, F1 signal, GObject * g2, F2 slot)
{

}

#endif // GOBJECT_H
