#include "Illuminate.h"

Illuminate::Illuminate(int r, int b, int g) {
	r = 200;
	col_r = r;
	col_g = g;
	col_b = b;
	calc();
}
void Illuminate::alphaplus() { alpha += 2 * (M_PI / (360)); }
void Illuminate::betaplus() { beta += 2 * (M_PI / (360)); }
void Illuminate::alphaminus() { alpha -= 2 * (M_PI / (360)); }
void Illuminate::betaminus() { beta -= 2 * (M_PI / (360)); }

void Illuminate::settype(int i)
{
	if (i > 2 || i < 0) i = 0;
	type = i;
}
int Illuminate::gettype() {
	return type;
}
void Illuminate::setcol(int r, int g, int b) {
	col_r = r;
	col_g = g;
	col_b = b;
}
int Illuminate::getr() { return col_r; }
int Illuminate::getg() { return col_g; }
int Illuminate::getb() { return col_b; }

void Illuminate::transformation(const double &teta, const double &phi) {
	calc();
	p2d.transformation(teta, phi);
}
void Illuminate::calc()
{
	p2d.setp3d(
		(r * sin(alpha)*cos(beta)),
		(r * sin(alpha)*sin(beta)),
		(r * cos(alpha)));
}
int Illuminate::getx() { return p2d.getp3d().getx(); }
int Illuminate::gety() { return p2d.getp3d().gety(); }
int Illuminate::getz() { return p2d.getp3d().getz(); }
Point3D Illuminate::getp3d() { return p2d.getp3d(); }
void Illuminate::draw(const HDC& dc) const {
	HBRUSH brush;
	brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(dc, brush);
	Ellipse(dc, p2d.getx(), p2d.gety(), p2d.getx() + 5, p2d.gety() + 5);
}