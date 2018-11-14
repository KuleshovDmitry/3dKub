#pragma once

class Point3D {
	double x, y, z;
public:
	void setx(const double value) { x = value; }
	void sety(const double value) { y = value; }
	void setz(const double value) { z = value; }
	void set(const double value1, const double value2, const double value3) 
	{ x = value1, y = value2, z = value3; }
	double getx() const { return x; }
	double gety() const { return y; }
	double getz() const { return z; }
};