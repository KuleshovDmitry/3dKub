#pragma once
#include "Point3D.h"
#include <math.h>

const int RRRX = 300, RRRY = 200;
const double M_PI = 3.14159265358979323846;
class Point2D {
	double x, y;
	bool f;
	Point3D p3d;
public:
	void transformation(const double &teta, const double &phi) ;
	void setp3d(const double x, const double y, const double z) { p3d.set(x, y, z); }
	Point3D getp3d() { return p3d; }
	void setx(const double value) { x = value; }
	void sety(const double value) { y = value; }
	void setf(const bool fl) { f = fl; }
	double getx() const { return x; }
	double gety() const { return y; }
	bool getf() const { return f; }
};