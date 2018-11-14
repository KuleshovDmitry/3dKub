#pragma once
#include "Point3D.h"
#include "Point2D.h"
#include <cmath>
#include <iostream>
#include <windows.h>
#include <GdiPlus.h>

class Illuminate {
	Point2D p2d;
	int r = 200;
	int col_r, col_g, col_b;
	int type = 0;
	double alpha = 3.14159265358979323846, beta = 0;
public:

	Illuminate(int r, int b, int g);

	void alphaplus();
	void betaplus();
	void alphaminus();
	void betaminus();
	void setcol(int r, int g, int b);
	void settype(int i);
	int gettype();
	int getr();
	int getg();
	int getb();
	void transformation(const double &teta, const double &phi);
	void calc();
	int getx();
	int gety();
	int getz();
	Point3D getp3d();
	void draw(const HDC& dc) const;
};