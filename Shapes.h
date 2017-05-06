#include "Base.h"
#include "Container.h"
#include <sstream>
#include <cmath>
#define M_PI 3.14159265358979323846

struct ExceptionInvertedShape {
	std::string nameShape;
};

class Point : public Shape, public Named {
public:
	Point() : Named( "" ) {}
	Point( std::string const & name, float const x, float const y ) : Named( name ) {
		m_x = x;
		m_y = y;
	}
	Point( Point const & point ) : Named( point.m_name ) {
		m_x = point.m_x;
		m_y = point.m_y;
	}
	std::string Print() {
		std::ostringstream out;
		out << "Point: " << m_name << " ( " << m_x << ", " << m_y << " )" << std::endl;
		return out.str();
	}
	float GetX() {
		return m_x;
	}
	float GetY() {
		return m_y;
	}
private:
	float m_x, m_y;
};

class Circle : public Shape, public Named {
public:
	Circle( std::string const & name, Point const & point, float const radius ) : Named( name ) {
		m_center = new Point( point );
		m_radius = radius;
		if( m_radius < 0 ) {
			ExceptionInvertedShape exception;
			exception.nameShape = name;
			throw exception;
		}
	}
	std::string Print() {
		std::ostringstream out;
		out << "Circle: " << m_name << std::endl
			<< "center: " << m_center->Print()
			<< "radius: " << m_radius << std::endl
			<< "area: " << M_PI * m_radius * m_radius << std::endl;
		return out.str();
	}
	~Circle() {
		delete m_center;
	}
private:
	Point * m_center;
	float m_radius;
};

class Rect : public Shape, public Named {
public:
	Rect( std::string const & name, Point const & pointUpLeft, Point const & pointDownRight ) : Named( name ) {
		m_pointUpLeft = new Point( pointUpLeft );
		m_pointDownRight = new Point( pointDownRight );
		if( m_pointDownRight->GetX() < m_pointUpLeft->GetX() || m_pointUpLeft->GetY() < m_pointDownRight->GetY() ) {
			ExceptionInvertedShape exception;
			exception.nameShape = name;
			throw exception;
		}
	}
	std::string Print() {
		std::ostringstream out;
		out << "Rect: " << m_name << std::endl
			<< "up left point: " << m_pointUpLeft->Print()
			<< "down right point: " << m_pointDownRight->Print()
			<< "area: " << ( m_pointDownRight->GetX() - m_pointUpLeft->GetX() ) * ( m_pointUpLeft->GetY() - m_pointDownRight->GetY() ) << std::endl;
		return out.str();
	}
	~Rect() {
		delete m_pointUpLeft;
		delete m_pointDownRight;
	}
protected:
	Point * m_pointUpLeft, * m_pointDownRight;
};

class Square : public Rect {
public:
	Square( std::string const & name, Point const & pointUpLeft, Point const & pointDownRight ) : Rect( name, pointUpLeft, pointDownRight ) {}
	std::string Print() {
		std::ostringstream out;
		out << "Square: " << m_name << std::endl
			<< "up left point: " << m_pointUpLeft->Print()
			<< "down right point: " << m_pointDownRight->Print()
			<< "area: " << (m_pointDownRight->GetX() - m_pointUpLeft->GetX()) * (m_pointUpLeft->GetY() - m_pointDownRight->GetY()) << std::endl;
		return out.str();
	}
};

class Polyline : public Shape, public Named {
public:
	Polyline( std::string const & name ) : Named( name ) {}
	void AddPoint( Point & point ) {
		m_points.AddLast( point );
	}
	std::string Print() {
		std::ostringstream out;
		out << "Polyline: " << m_name << std::endl;
		out << "length: " << CalculateLength() << std::endl;
		return out.str();
	}
protected:
	float CalculateLength() {
		float lenght = 0;
		int size = m_points.GetSize();
		for( int i = 0; i < size - 1; ++i ) {
			Point point1 = m_points[i];
			Point point2 = m_points[i+1];
			lenght += sqrt( pow( point1.GetX() - point2.GetX(), 2 ) + pow( point1.GetY() - point2.GetY(), 2 ) );
		}
		return lenght;
	}

	Container< Point > m_points;
};

class Polygon : public Polyline {
public:
	Polygon( std::string const & name ) : Polyline( name ) {}
	std::string Print() {
		std::ostringstream out;
		out << "Polygon: " << m_name << std::endl;
		out << "perimeter: " << CalculateLength() << std::endl;
		return out.str();
	}
private:
	float CalculateLength() {
		float lenght = 0;
		Point point1 = m_points.GetFirst();
		Point point2 = m_points.GetLast();
		lenght = sqrt( pow( point1.GetX() - point2.GetX(), 2 ) + pow( point1.GetY() - point2.GetY(), 2 ) );
		return Polyline::CalculateLength() + lenght;
	}
};