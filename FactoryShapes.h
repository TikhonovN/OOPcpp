#include "Shapes.h"
#include <cstdlib>
#include <ctime>

Point * CreatePoint() {
	float x = 0.01f * ( rand() % 10001 );
	float y = 0.01f * ( rand() % 10001 );
	Point * point = new Point( "thisPoint", x, y );
	return point;
}

Shape * CreateShape( int const typeShape ) {
	enum {
		point,
		circle,
		rect,
		square,
		polyline,
		polygon
	};
	switch( typeShape ) {
		case point : {
			Point * point = CreatePoint();
			return point;
		}
		case circle : {
			Point * center = CreatePoint();
			float radius = 0.01f * ( rand() % 10001 );
			Circle * circle = new Circle( "thisCircle", * center, radius );
			delete center;
			return circle;
		}
		case rect : {
			float width = 0.01f * ( rand() % 10000 ) + 0.01f;
			float height = 0.01f * ( rand() % 10000 ) + 0.01f;
			Point * pointUpLeft = CreatePoint();
			Point * pointDownRight = new Point( "thisPoint", pointUpLeft->GetX() + width, pointUpLeft->GetY() - height );
			Rect * rect = new Rect( "thisRect", * pointUpLeft, * pointDownRight );
			delete pointUpLeft;
			delete pointDownRight;
			return rect;
		}
		case square: {
			float side = 0.01f * ( rand() % 10000 ) + 0.01f;
			Point * pointUpLeft = CreatePoint();
			Point * pointDownRight = new Point( "thisPoint", pointUpLeft->GetX() + side, pointUpLeft->GetY() - side );
			Square * square = new Square( "thisSquare", * pointUpLeft, * pointDownRight );
			delete pointUpLeft;
			delete pointDownRight;
			return square;
		}
		case polyline : {
			int n = rand() % 16 + 5;
			Polyline * polyline = new Polyline( "thisPolyline" );
			for( int i = 0; i < n; ++i ) {
				Point * point = CreatePoint();
				polyline->AddPoint( * point );
				delete point;
			}
			return polyline;
		}
		case polygon : {
			int n = rand() % 16 + 5;
			Polygon * polygon = new Polygon( "thisPolygon" );
			for( int i = 0; i < n; ++i ) {
				Point * point = CreatePoint();
				polygon->AddPoint( * point );
				delete point;
			}
			return polygon;
		}
		default: return nullptr;
	}
}