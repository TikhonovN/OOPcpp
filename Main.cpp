#include "FactoryShapes.h"

int main() {
	
	Container < Shape * > shapes;
	srand( (unsigned int) time( 0 ) );
	for( int i = 0; i < 30; ++i ) {
		int typeShape = rand() % 6;
		try {
			Shape * shape = CreateShape( typeShape );
			shapes.AddLast( shape );
		}
		catch( ExceptionInvertedShape exception ) {
			std::cout << "Inverted shape: " << exception.nameShape << std::endl;
		}
	}
	std::cout << "Quantity of shapes: " << Shape::GetCount() << std::endl << std::endl;

	int size = shapes.GetSize();
	for( int i = 0; i < size; ++i ) {
		Shape * shape = shapes.GetFirst();
		std::cout << shape->Print() << std::endl;
		delete shape;
		shapes.DeleteFirst();
	}

	std::cout << "Quantity of shapes: " << Shape::GetCount() << std::endl;
	system( "pause" );
	return 0;
}