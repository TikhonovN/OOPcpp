#include<iostream>
#include<string>

class Printable {
public:
	virtual std::string Print() = 0;
};

class Named : virtual public Printable {
public:
	Named( std::string const & name ) {
		m_name = name;
	}
protected:
	std::string m_name;
};

class Shape : virtual public Printable {
public:
	Shape() {
		++sm_count;
	}
	virtual ~Shape() {
		--sm_count;
	}
	static int GetCount() {
		return sm_count;
	}
private:
	static unsigned int sm_count;
};

unsigned int Shape::sm_count = 0;

std::ostream & operator << ( std::ostream & ioStream, Printable & printable ) {
	return ioStream << printable.Print() << std::endl;
}