#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H
class Noncopyable
{
	protected:
	Noncopyable(){};
	~Noncopyable(){};

	private:
	Noncopyable(const Noncopyable&);
	Noncopyable& operator=(const Noncopyable&);
};
#endif
