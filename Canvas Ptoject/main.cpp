#include "Canvas.h"

int main() {

	// Creating Shapes and Getting Their Areas
	Shape Circle(0, 0, 5), Rectangle(0, 0, 5, 10), Square(0, 0, 5, 5), Triangle(0, 0, 10, 5, 3);
	cout << "Area of Square is :" << Square.getArea() << endl;
	cout << "Area of Circle is :" << Circle.getArea() << endl;
	cout << "Area of Rectangle is :" << Rectangle.getArea() << endl;
	cout << "Area of Triangle is :" << Triangle.getArea() << endl;

	// Working On Canvas

	Canvas C;
	Shape s_Obj(2, 2, 10); //circle made at center 2,2 and radius=10
	Shape triangle(1, 2, 4, 5, 1), square(4,2,8,8), rectangle(3, 4, 4, 7);
	cout << "\nAdding Circle to Canvas C...\n";
	C["Circle"] += s_Obj; //should add the object to the canvas
	cout << "\nAdding Square to Canvas C...\n";
	C["Square"] += square; // Adding Square to Canvas
	cout << "Canvas C: " << string(C) << endl << endl;
	
	C(0, 1); //prints a certain shape in the canvas
	Canvas C1;
	cout << "\nAdding Triangle to Canvas C1\n";
	C1["Triangle"] += triangle;		// Adding Triangle to Canvas C1
	cout << "\nAdding Rectangle to Canvas C1\n";
	*(*(*(C1["Rectangle"]))) = rectangle; //rectangle is added to Canvas C1
	cout << "Canvas C1: " << string(C1) << endl;
	

	// Creating Canvas 3 from C1 and C
	Canvas C3;
	C3 = C1 + C;
	cout << "\nCanvas 3 = (C1 + C) : " << string(C3) << endl;
	return 0;
}