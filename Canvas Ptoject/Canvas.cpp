#include "Canvas.h"

const int TYPE_OF_SHAPES_PER_CANVAS = 10;

//<---------------<-POINT CLASS FUNCTIONS->----------------->

Point::Point() {
	X = 0;
	Y = 0;
}
Point::Point(int x, int y) {
	X = x;
	Y = y;
}

//<============== SHAPE CLASS FUNCTIONS =================>

Shape::Shape() {
	Length = 0;
	Width = 0;
	Height = 0;
	Base = 0;
	Radius = 0;
	NoOfSides = 0;
	point = nullptr;
}

Shape::Shape(int x, int y, int radius) {
	Length = 0;
	Width = 0;
	Height = 0;
	Base = 0;
	Radius = radius;
	NoOfSides = 0;
	point = new Point[1];
	point[0].setXY(x, y);
}

Shape::Shape(int x, int y, int length, int width) {
	Length = length;
	Width = width;
	Height = 0;
	Base = 0;
	Radius = 0;
	NoOfSides = 4;
	point = new Point[4];
	point[0].setXY(x, y);
	point[1].setXY(point[0].getX(), point[0].getY() + Length);
	point[2].setXY(point[0].getX() + Width, point[0].getY() + Length);
	point[3].setXY(point[0].getX() + Width, point[0].getY());
}

Shape::Shape(int x, int y, int base, int height, int sides) {
	Length = 0;
	Width = 0;
	Height = height;
	Base = base;
	Radius = 0;
	NoOfSides = 3;
	point = new Point[3];
	point[0].setXY(x, y);
	point[1].setXY(point[0].getX() + Width / 2, point[0].getY() + Length);
	point[2].setXY(point[0].getX() + Width, point[0].getY());
}

Shape::Shape(Shape& obj) {
	Length = obj.Length;
	Width = obj.Width;
	Height = obj.Height;
	Base = obj.Base;
	Radius = obj.Radius;
	NoOfSides = obj.NoOfSides;
	int length_Array = NoOfSides;
	if (NoOfSides == 0 && Radius != 0) { length_Array = 1; }
	point = new Point[length_Array];
	for (int i = 0; i < length_Array; i++) {
		point[i].setXY(obj.point[i].getX(), obj.point[i].getY());
	}
}

Shape& Shape::operator=(Shape& obj) {
	delete[] point;
	Length = obj.Length;
	Width = obj.Width;
	Height = obj.Height;
	Base = obj.Base;
	Radius = obj.Radius;
	NoOfSides = obj.NoOfSides;
	int length_Array = NoOfSides;
	if (NoOfSides == 0 && Radius != 0) { length_Array = 1; }
	point = new Point[length_Array];
	for (int i = 0; i < length_Array; i++) {
		point[i].setXY(obj.point[i].getX(), obj.point[i].getY());
	}
	return *this;
}

Shape& Shape::operator+=(Shape& obj) {
	Length += obj.Length;
	Width += obj.Width;
	Height += obj.Height;
	Base += obj.Base;
	Radius += obj.Radius;
	for (int i = 0; i < NoOfSides; i++) {
		point[i].setXY(point[i].getX() + obj.point[i].getX(), point[i].getY() + obj.point[i].getY());
	}
	return *this;
}

int Shape::operator[](string temp) {
	if (temp == "Length") { return Length; }
	else if (temp == "Width") { return Width; }
	else if (temp == "Base") { return Base; }
	else if (temp == "Height") { return Height; }
	else if (temp == "Radius") { return Radius; }
}

bool Shape::operator==(Shape& obj) {
	if (Length != obj.Length) {
		return false;
	}
	if (Width != obj.Width) {
		return false;
	}
	if (Height != obj.Height) {
		return false;
	}
	if (Base != obj.Base) {
		return false;
	}
	if (Radius != obj.Radius) {
		return false;
	}
	if (NoOfSides != obj.NoOfSides) {
		return false;
	}
	for (int i = 0; i < NoOfSides; i++) {
		if (point[i].getX() != obj.point[i].getX()) {
			return false;
		}
		if (point[i].getY() != obj.point[i].getY()) {
			return false;
		}
	}
	return true;
}

void Shape::Print() {
	if (Radius != 0) {
		cout << "Type Of Shape: Circle" << endl;
		cout << "Radius : " << Radius << endl;
		cout << "Center : (" << point[0].getX() << ", " << point[0].getY() << ')' << endl;
	}
	else if (Length != 0 && Length != Width) {
		cout << "Type Of Shape: Rectangle" << endl;
		cout << "Length : " << Length << endl;
		cout << "Width : " << Width << endl;
		cout << "Start Point : (" << point[0].getX() << ", " << point[0].getY() << ')' << endl;
	}
	else if (Length != 0 && Length == Width) {
		cout << "Type Of Shape: Square" << endl;
		cout << "Length : " << Length << endl;
		cout << "Width : " << Width << endl;
		cout << "Start Point : (" << point[0].getX() << ", " << point[0].getY() << ')' << endl;
	}
	else if (NoOfSides == 3) {
		cout << "Type Of Shape: Traiangle" << endl;
		cout << "Base : " << Base << endl;
		cout << "Height : " << Height << endl;
		cout << "Start Point : (" << point[0].getX() << ", " << point[0].getY() << ')' << endl;
	}
}

int Shape::getArea() {
	if (Base != 0) {
		return 0.5 * Height * Base;
	}
	else if (Length != 0) {
		return Length * Width;
	}
	else if (Radius != 0) {
		return 3.14 * Radius * Radius;
	}
	cout << "The Shape do not Exist\n";
	return 0;
}

//<============== NODE CLASS FUNCTIONS =================>

node::node() {
	Shape temp(0, 0, 0, 0);
	value = temp;
	next = nullptr;
}

node::node(Shape& obj) {
	value = obj;
	next = nullptr;
}

node::node(Shape& obj, node* ptr) {
	value = obj;
	next = ptr;
}

node::node(node& obj) {
	value = obj.value;
	next = obj.next;
}

node& node::operator=(Shape obj) {
	node* ptr = this;
	if (ptr == nullptr) {
		ptr = new node(obj);
	}
	else if (ptr->next == nullptr)
	{
		ptr->next = new node(obj);
	}
	else {
		node* ptr1 = ptr->next;
		ptr->next = new node(obj, ptr1);
	}
	cout << "Shape Added Successfully\n";
	return *this;
}

//<============== CANVAS CLASS FUNCTIONS =================>


Canvas::Canvas() {// a default constructor
	first = nullptr;
	size = 0;
}

Canvas::Canvas(int Size) {// a parametrized constructor initializing an Array
	first = new node;
	size = 1;
	node* ptr = first;
	for (int i = 0; i < Size - 1; i++) {
		while (true) {
			if (ptr->next == nullptr) {
				ptr->next = new node;
				size++;
				break;
			}
			ptr = ptr->next;
		}
	}
}

Canvas::Canvas(Shape* arr, int Size) {
	int count = 0;
	first = new node(arr[count++]);
	size = 1;
	node* ptr = first;
	for (int i = 0; i < Size - 1; i++) {
		while (true) {
			if (ptr->next == nullptr) {
				ptr->next = new node(arr[count++]);
				size++;
				break;
			}
			ptr = ptr->next;
		}
	}
}

Shape& Canvas::operator[](Shape& obj) {
	node* ptr = first;
	for (int i = 0; i < size; i++) {
		if (ptr->value == obj) {
			return ptr->value;
		}
		ptr = ptr->next;
	}
	cout << "No Shape Found...\n";
	return ptr->value;
}

void Canvas::UpdateSize() {
	int count = 0;
	node* ptr = first;
	for (int i = 0; ptr != nullptr; i++) {
		count++;
		ptr = ptr->next;
	}
	size = count;
}

node*** Canvas::operator[](string type) {
	UpdateSize();
	node* ptr = first;
	int count = 0;
	if (type == "Circle") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getRadius() != 0) { count++; }
		}
	}

	else if (type == "Rectangle") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() != ptr->value.getWidth())) { count++; }
		}
	}

	else if (type == "Square") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() == ptr->value.getWidth())) { count++; }
		}
	}

	else if (type == "Triangle") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 3) { count++; }
		}
	}

	node*** ShapesType = new node * *[count];
	ShapesType[0] = &first;
	for (int i = 1; i < count; i++) {
		ShapesType[i] = nullptr;
	}

	ptr = first;

	if (type == "Circle") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getRadius() != 0) {
				ShapesType[i] = &ptr;
			}
		}
	}

	else if (type == "Rectangle") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() != ptr->value.getWidth())) { ShapesType[i] = &ptr; }
		}
	}

	else if (type == "Square") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() == ptr->value.getWidth())) { ShapesType[i] = &ptr; }
		}
	}

	else if (type == "Triangle") {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 3) { ShapesType[i] = &ptr; }
		}
	}

	return ShapesType;
}

void Canvas::operator()(int type, int ShapeNumber) { //prints the information of specific shape in the canvas
	// 0 -> Circle, 1 -> Rectangle, 2 -> Square, 3 -> Triangle
	UpdateSize();
	int count = 0;
	node* ptr = first;
	if (type == 0) {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getRadius() != 0) { count++; }
		}
	}

	else if (type == 1) {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() != ptr->value.getWidth())) { count++; }
		}
	}

	else if (type == 2) {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() == ptr->value.getWidth())) { count++; }
		}
	}

	else if (type == 3) {
		for (int i = 0; i < size; i++) {
			if (ptr->value.getNoOfSides() == 3) { count++; }
		}
	}

	if (type == 0 && ShapeNumber > 0 && ShapeNumber <= count) {
		node*** ptr = operator[]("Circle");
		ptr[ShapeNumber - 1][0]->value.Print();
	}

	else if (type == 1 && ShapeNumber > 0 && ShapeNumber <= count) {
		node*** ptr = operator[]("Rectangle");
		ptr[ShapeNumber - 1][0]->value.Print();
	}
	else if (type == 2 && ShapeNumber > 0 && ShapeNumber <= count) {
		node*** ptr = operator[]("Square");
		ptr[ShapeNumber - 1][0]->value.Print();
	}
	else if (type == 3 && ShapeNumber > 0 && ShapeNumber <= count) {
		node*** ptr = operator[]("Triangle");
		ptr[ShapeNumber - 1][0]->value.Print();
	}

	else {
		cout << "Shape Not Exist...\n";
	}
}

Canvas& Canvas::operator+(Canvas& obj) {//adds two canvas and creates a third one with shapes of
	//first two canvases – be careful of the limit of shapes per canvas
	UpdateSize();
	obj.UpdateSize();
	int noOfSquare = 0, noOfRectangle = 0, noOfCircle = 0, noOfTriangle = 0;
	node* ptr = first;
	for (int i = 0; i < size; i++) {
		if (ptr->value.getRadius() != 0) { noOfCircle++; }
		if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() != ptr->value.getWidth())) { noOfRectangle++; }
		if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() == ptr->value.getWidth())) { noOfSquare++; }
		if (ptr->value.getNoOfSides() == 3) { noOfTriangle++; }
		ptr = ptr->next;
	}
	int RectangleMAX = TYPE_OF_SHAPES_PER_CANVAS;
	int TriangleMAX = TYPE_OF_SHAPES_PER_CANVAS;
	int SquareMAX = TYPE_OF_SHAPES_PER_CANVAS;
	int CircleMAX = TYPE_OF_SHAPES_PER_CANVAS;

	ptr = obj.first;
	for (int i = 0; i < obj.size; i++) {
		if (ptr->value.getRadius() != 0) { noOfCircle++; }
		if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() != ptr->value.getWidth())) { noOfRectangle++; }
		if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() == ptr->value.getWidth())) { noOfSquare++; }
		if (ptr->value.getNoOfSides() == 3) { noOfTriangle++; }
		ptr = ptr->next;
	}
	ptr = first;
	int increment = 0;
	Shape* arr = new Shape[noOfSquare + noOfRectangle + noOfCircle + noOfTriangle];
	for (int i = 0; i < size; i++) {
		if (ptr->value.getRadius() != 0 && CircleMAX > 0) { arr[increment++] = ptr->value; CircleMAX--; }
		else if (ptr->value.getBase() != 0 && TriangleMAX > 0) { arr[increment++] = ptr->value; TriangleMAX--; }
		else if (ptr->value.getLength() != 0 && ptr->value.getLength() != ptr->value.getWidth() && RectangleMAX > 0) { arr[increment++] = ptr->value; RectangleMAX--; }
		else if (ptr->value.getLength() != 0 && ptr->value.getLength() == ptr->value.getWidth() && SquareMAX > 0) { arr[increment++] = ptr->value; SquareMAX--; }
		ptr = ptr->next;
	}
	ptr = obj.first;
	for (int i = 0; i < obj.size; i++) {
		if (ptr->value.getRadius() != 0 && CircleMAX > 0) { arr[increment++] = ptr->value; CircleMAX--; }
		else if (ptr->value.getBase() != 0 && TriangleMAX > 0) { arr[increment++] = ptr->value; TriangleMAX--; }
		else if (ptr->value.getLength() != 0 && ptr->value.getLength() != ptr->value.getWidth() && RectangleMAX > 0) { arr[increment++] = ptr->value; RectangleMAX--; }
		else if (ptr->value.getLength() != 0 && ptr->value.getLength() == ptr->value.getWidth() && SquareMAX > 0) { arr[increment++] = ptr->value; SquareMAX--; }
		ptr = ptr->next;
	}

	if (CircleMAX == 0) { cout << "Circle Limit Reached...\n"; }
	if (RectangleMAX == 0) { cout << "Rectangle Limit Reached...\n"; }
	if (TriangleMAX == 0) { cout << "Triangle Limit Reached...\n"; }
	if (SquareMAX == 0) { cout << "Square Limit Reached...\n"; }

	Canvas* add = new Canvas(arr, noOfSquare + noOfRectangle + noOfCircle + noOfTriangle);
	add->size = noOfSquare + noOfRectangle + noOfCircle + noOfTriangle;
	return *add;
}

Canvas::operator string() {
	UpdateSize();
	int noOfSquare = 0, noOfRectangle = 0, noOfCircle = 0, noOfTriangle = 0;
	node* ptr = first;
	for (int i = 0; i < size; i++) {
		if (ptr->value.getRadius() != 0) { noOfCircle++; }
		if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() != ptr->value.getWidth())) { noOfRectangle++; }
		if (ptr->value.getNoOfSides() == 4 && (ptr->value.getLength() == ptr->value.getWidth())) { noOfSquare++; }
		if (ptr->value.getNoOfSides() == 3) { noOfTriangle++; }
		ptr = ptr->next;
	}
	string temp = "";
	temp += "Canvas Size: " + to_string(size) + ", Squares: " + to_string(noOfSquare) + ", Rectangle: " + to_string(noOfRectangle) + ", Triangle: " + to_string(noOfTriangle) + ", Circle: " + to_string(noOfCircle);
	return temp;
}

Canvas::~Canvas() {
	node* ptr_next = nullptr;
	for (int i = 0; i < size; i++) {
		ptr_next = first->next;
		delete first;
		first = ptr_next;
	}
	delete first;
}

//<============>  NON MEMBER FUNCTIONS <=============>

node*** operator+=(node*** arr, Shape& obj) {
	node*** ptr = &arr[0];
	if (**ptr == nullptr) {
		**ptr = new node(obj);
	}
	else if ((*(*ptr))->next == nullptr)
	{
		(*(*ptr))->next = new node(obj);
	}
	else {
		node* ptr1 = (*(*ptr))->next;
		(*(*ptr))->next = new node(obj, ptr1);
	}
	cout << "Shape Added Successfully\n";
	return arr;
}
