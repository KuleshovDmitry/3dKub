#pragma once
#include "Point3D.h"
#include "Point2D.h"
#include <math.h >
#include <windows.h>
#include <GdiPlus.h>
#include "Illuminate.h"

class Cube {
	Point2D p2d[8];
	Gdiplus::Point edges[6][4];
public:
	Cube(int size);

	void transformation(const double &teta, const double &phi, Illuminate& ill);

	void draw(HDC& hdc, HWND hWnd, Illuminate& ill, const double &teta, const double &phi) const;

};