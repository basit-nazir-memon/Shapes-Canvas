#pragma once
#include <iostream>
#include <string>
using namespace std;

class Point {
	int X;
	int Y;
public:
	Point();
	Point(int, int);

	void setXY(int x, int y) {
		X = x;
		Y = y;
	}
	int getX() { return X; }
	int getY() { return Y; }

};

class Shape {
	int Length;
	int Width;
	int Height;
	int Base;
	int Radius;
	int NoOfSides;
	Point* point;
public:
	 // CONSTRUCTORS
	Shape();		// Default Constructors
	Shape(int, int, int); // Circle Constructor
	Shape(int, int , int, int); // Rectangle And Square Constructor
	Shape(int, int, int, int, int); // Triangle Constructor
	Shape(Shape&); // Copy COnstructor

	Shape& operator=(Shape&); // Assignment Operator

	Shape& operator+=(Shape&);	// Adds a shape in existing shape

	int operator[](string);	// whenever you have to access any information of shape

	bool operator==(Shape&);	// Check both Shape are Same

	void Print();		// Prints Shape Information

	int getArea();		// return Area of Shape

	// GETTERS 
	int getLength() { return Length; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	int getBase() { return Base; }
	int getRadius() { return Radius; }
	int getNoOfSides() { return NoOfSides; }

};

struct node {
	node* next;
	Shape value;

	node();

	node(Shape&);

	node(Shape&, node*);

	node(node&);
	
	node& operator=(Shape);
};

class Canvas
{
public:
	node* first;
	int size;
public:
	Canvas();// a default constructor
	
	Canvas(int Size);// a parametrized constructor initializing an Array
	
	Canvas(Shape* arr, int Size);

	Shape& operator[](Shape& obj);

	void UpdateSize();
	
	node*** operator[](string type);
	
	void operator()(int type, int ShapeNumber);
	
	Canvas& operator+(Canvas& obj); //adds two canvas and creates a third one with shapes of

	operator string();

	~Canvas();
};

node*** operator+=(node*** arr, Shape& obj);