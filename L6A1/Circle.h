#pragma once
#include "Point.h"
#include <iostream>
#include <sstream>
#include "OneDimObject.h"

using namespace std;

extern bool debugConstructor;

class Circle : public OneDimObject
{
private:
	Point centre;
	double radius;
public:

	Circle(double x = 0, double y = 0, double r = 0);
	Circle(const Point& centre = Point(), double r = 1.0);
	Circle(const string& str);
	Circle(const char* c);

	~Circle();

	const Point& getCentre() const;
	double getRadius() const;
	void setCentre(double x, double y);
	void setCentre(Point p);
	void setRadius(double r);

	void move(double dx, double dy);
	void print(bool b = true) const;
	string toString() const;

	friend istream& operator >> (istream& is, Circle& c);
	friend ostream& operator << (ostream& os, Circle& c);
};

Circle::Circle(double x, double y, double r) : centre(x, y), radius(r) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Circle, Objekt: " << getId() << endl;
};

Circle::Circle(const Point& p, double r) : centre(p), radius(r) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Circle, Objekt: " << getId() << endl;
};

Circle::Circle(const string& str) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Circle, Objekt: " << getId() << endl;
	stringstream buf(str);
	buf >> *this;
}

Circle::Circle(const char* c) {
	if (debugConstructor)
		cout << "Konstruktor der Klasse Circle, Objekt: " << getId() << endl;
	stringstream buf(c);
	buf >> *this;
}

Circle::~Circle() {
	if (debugConstructor)
		cout << "Destruktor der Klasse Circle, Objekt: " << getId() << endl;
}

const Point& Circle::getCentre() const {
	return centre;
}

double Circle::getRadius() const {
	return radius;
}

void Circle::setCentre(double x, double y) {	//Überladung 1 mit Koordinaten
	this->centre.setX(x);
	this->centre.setY(y);

}

void Circle::setCentre(Point p) {	//Überladung 2 mit Punkt
	this->centre = p;
}

void Circle::setRadius(double r) {
	this->radius = r;
}

void Circle::move(double dx, double dy) {
	this->centre.move(dx, dy);
}

void Circle::print(bool b) const {
	std::cout << "<";
	centre.print(false);
	std::cout << ", " << getRadius() << ">";
	if (b) std::cout << std::endl;
}

string Circle::toString() const {
	stringstream buf;
	buf << "<";
	buf << getCentre().toString();
	buf << ", " << this->radius << ">";
	return buf.str();
}

istream& operator >>(istream& is, Circle& c) {
	bool started = false;
	bool done = false;
	while (!is.eof() && !done) {
		switch (is.get()) {
		case '<':
			if (!started) {
				is >> c.centre;
			}
			started = true;
			break;
		case ',':
			if (started) {
				is >> c.radius;
			}
			break;
		case '>':
			done = true;
			break;
		default:
			break;
		}

	}
	return is;
}

ostream& operator <<(ostream& os, Circle& c) {
	os << c.toString();
	return os;
}