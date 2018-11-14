#include "Cube.h"


Cube::Cube(const int size) {
	p2d[0].setp3d(-size, -size, -size),
		p2d[1].setp3d(size, -size, -size),
		p2d[2].setp3d(size, size, -size),
		p2d[3].setp3d(-size, size, -size),
		p2d[4].setp3d(-size, -size, size),
		p2d[5].setp3d(size, -size, size),
		p2d[6].setp3d(size, size, size),
		p2d[7].setp3d(-size, size, size);
}

void Cube::transformation(const double &teta, const double &phi, Illuminate& ill) {

	ill.transformation(teta, phi);
	int bufphi = phi * 360 / M_PI;
	while (bufphi > 360)
	{
		bufphi = bufphi - 360;
	}
	while (bufphi < 0)
	{
		bufphi = bufphi + 360;
	}

	for (int i = 0; i < 8; i++) {
		p2d[i].transformation(teta, phi);

		if ((-p2d[i].getp3d().getx()*(-cos(phi) * cos(teta)) < 0) && (p2d[i].getp3d().gety()*(cos(phi) * sin(teta)) < 0) && (p2d[i].getp3d().getz()*(sin(phi)) < 0)) {
			if (bufphi <= 180) p2d[i].setf(true);
			else p2d[i].setf(false);
		}
		if ((p2d[i].getp3d().getx()*(-cos(phi) * cos(teta)) < 0) && (-p2d[i].getp3d().gety()*(cos(phi) * sin(teta)) < 0) && (-p2d[i].getp3d().getz()*(sin(phi)) < 0))
		{
			if (bufphi < 180) p2d[i].setf(false);
			else p2d[i].setf(true);
		}
	}
}

void Cube::draw(HDC& hdc, HWND hWnd, Illuminate& ill, const double &teta, const double &phi) const {

	Gdiplus::Point Pnt[8];
	int region1, region2;
	if (ill.gettype() == 1) { region1 = 15; region2 = 15; }
	else if (ill.gettype() == 2) {
		region1 = 30; region2 = 75;
	}
	else { region1 = 75; region2 = 75; }
	Gdiplus::GraphicsPath path2[6];
	bool edges_flag[6];

	for (int i = 0; i < 8; i++) {
		Pnt[i].X = p2d[i].getx();
		Pnt[i].Y = p2d[i].gety();
	}
	if (p2d[0].getf() && p2d[1].getf() && p2d[2].getf() && p2d[3].getf()) edges_flag[0] = false; else true;
	if (p2d[0].getf() && p2d[1].getf() && p2d[5].getf() && p2d[4].getf()) edges_flag[1] = false; else true;
	if (p2d[0].getf() && p2d[4].getf() && p2d[7].getf() && p2d[3].getf()) edges_flag[2] = false; else true;
	if (p2d[2].getf() && p2d[3].getf() && p2d[7].getf() && p2d[6].getf()) edges_flag[3] = false; else true;
	if (p2d[4].getf() && p2d[5].getf() && p2d[6].getf() && p2d[7].getf()) edges_flag[4] = false; else true;
	if (p2d[1].getf() && p2d[2].getf() && p2d[6].getf() && p2d[5].getf()) edges_flag[5] = false; else true;

	Gdiplus::Point edges[6][4] = {
		{ Pnt[0], Pnt[1], Pnt[2], Pnt[3] },
		{ Pnt[0], Pnt[1], Pnt[5], Pnt[4] },
		{ Pnt[0], Pnt[4], Pnt[7], Pnt[3] },
		{ Pnt[2], Pnt[3], Pnt[7], Pnt[6] },
		{ Pnt[4], Pnt[5], Pnt[6], Pnt[7] },
		{ Pnt[1], Pnt[2], Pnt[6], Pnt[5] }
	};

	int flag_poz_ill[3];
	if (ill.getp3d().getx() > 75)
		flag_poz_ill[0] = 75;
	else if (ill.getp3d().getx() < -75)
		flag_poz_ill[0] = -75;
	else flag_poz_ill[1] = 0;
	if (ill.getp3d().gety() > 75)
		flag_poz_ill[1] = 75;
	else if (ill.getp3d().gety() < -75)
		flag_poz_ill[1] = -75;
	else flag_poz_ill[1] = 0;
	if (ill.getp3d().getz() > 75)
		flag_poz_ill[2] = 75;
	else if (ill.getp3d().getz() < -75)
		flag_poz_ill[2] = -75;
	else flag_poz_ill[2] = 0;
	bool dr_fl[3];
	bool grad_flag[6];
	for (int i = 0; i < 6; i++)
	{
		int r = 270;
		Gdiplus::Point pts1[] = { Gdiplus::Point(r , 0),
			Gdiplus::Point(r *0.866 ,r / 2),
			Gdiplus::Point(r / 2 ,r *0.866),

			Gdiplus::Point(0,r),
			Gdiplus::Point(-r / 2 ,r *0.866),
			Gdiplus::Point(-r * 0.866 ,r / 2),

			Gdiplus::Point(-r , 0),
			Gdiplus::Point(-r * 0.866 ,-r / 2),
			Gdiplus::Point(-r / 2 ,-r * 0.866),

			Gdiplus::Point(0,-r),
			Gdiplus::Point(r / 2 ,-r * 0.866),
			Gdiplus::Point(r *0.866 ,-r / 2),
			Gdiplus::Point(r , 0) };
		int ill2Dx, ill2Dy;
		int ill_pozx, ill_pozy, ill_pozz;
		if (i == 0 || i == 4)
		{
			if (i == 0) {
				ill_pozz = -75;
				if (ill.getz() > -region1)  grad_flag[i] = false;
				else grad_flag[i] = true;
			}
			else {
				ill_pozz = 75;
				if (ill.getz() < region1)  grad_flag[i] = false;
				else grad_flag[i] = true;
			}
			ill_pozx = ill.getx();
			ill_pozy = ill.gety();
			for (int j = 0; j < 13; j++)
			{
				if (i == 0)ill_pozz = -75;
				else ill_pozz = 75;
				int buffx = pts1[j].X, buffy = pts1[j].Y;
				pts1[j] = Gdiplus::Point(((buffx + ill_pozx)*(-sin(teta)) + (buffy + ill_pozy)*(cos(teta)) + RRRX), ((buffx + ill_pozx)*(-cos(phi) * cos(teta)) - (buffy + ill_pozy)*cos(phi) * sin(teta) + ill_pozz * (sin(phi)) + RRRY));
			}
			ill2Dx = ill_pozx * (-sin(teta)) + ill_pozy * (cos(teta)) + RRRX;
			ill2Dy = ill_pozx * (-cos(phi) * cos(teta)) - ill_pozy * cos(phi) * sin(teta) + ill_pozz * (sin(phi)) + RRRY;
		}
		else if (i == 2 || i == 5)
		{
			if (i == 2) {
				ill_pozx = -75;
				if (ill.getx() > -region2)  grad_flag[i] = false;
				else grad_flag[i] = true;
			}
			else {
				ill_pozx = 75;
				if (ill.getx() < region2)  grad_flag[i] = false;
				else grad_flag[i] = true;
			}
			ill_pozz = ill.getz();
			ill_pozy = ill.gety();
			ill2Dx = ill_pozx * (-sin(teta)) + ill_pozy * (cos(teta)) + RRRX;
			ill2Dy = ill_pozx * (-cos(phi) * cos(teta)) - ill_pozy * cos(phi) * sin(teta) + ill_pozz * (sin(phi)) + RRRY;
			for (int j = 0; j < 13; j++)
			{
				int buffx = pts1[j].X, buffy = pts1[j].Y;
				pts1[j] = Gdiplus::Point(((ill_pozx)*(-sin(teta)) + (buffy + ill_pozy)*(cos(teta)) + RRRX), ((ill_pozx)*(-cos(phi) * cos(teta)) - (buffy + ill_pozy)*cos(phi) * sin(teta) + (ill_pozz + buffx)*(sin(phi)) + RRRY));
			}
		}
		else if (i == 1 || i == 3)
		{
			if (i == 1) {
				ill_pozy = -75;
				if (ill.gety() > -region2)  grad_flag[i] = false;
				else grad_flag[i] = true; grad_flag[3] = !grad_flag[i];
			}
			else {
				ill_pozy = 75;
				if (ill.gety() < region2)  grad_flag[i] = false;
				else grad_flag[i] = true; grad_flag[1] = !grad_flag[i];
			}
			ill_pozx = ill.getx();
			ill_pozz = ill.getz();
			ill2Dx = ill_pozx * (-sin(teta)) + ill_pozy * (cos(teta)) + RRRX;
			ill2Dy = ill_pozx * (-cos(phi) * cos(teta)) - ill_pozy * cos(phi) * sin(teta) + ill_pozz * (sin(phi)) + RRRY;
			for (int j = 0; j < 13; j++)
			{
				int buffx = pts1[j].X, buffy = pts1[j].Y;
				pts1[j] = Gdiplus::Point(((ill_pozx + buffx)*(-sin(teta)) + (ill_pozy)*(cos(teta)) + RRRX), ((ill_pozx + buffx)*(-cos(phi) * cos(teta)) - (ill_pozy)*cos(phi) * sin(teta) + (ill_pozz + buffy)*(sin(phi)) + RRRY));
			}
		}

		Gdiplus::Graphics graphics(hdc);
		path2[i].AddCurve(pts1, 13);
		path2[i].CloseFigure();
		Gdiplus::PathGradientBrush pthGrBrush(&path2[i]);
		pthGrBrush.SetCenterPoint(Gdiplus::Point(ill2Dx, ill2Dy));

		pthGrBrush.SetCenterColor(Gdiplus::Color(255, ill.getr(), ill.getg(), ill.getb()));
		Gdiplus::Color colors[] = { Gdiplus::Color(255, 0, 0, 0) };
		int count = 1;
		pthGrBrush.SetSurroundColors(colors, &count);
		if (edges_flag[i])
			if (grad_flag[i]) {
				if (ill.gettype() == 2) {
					if (i == 0 || i == 4)
						pthGrBrush.SetFocusScales(0.01f, 0.01f);
					else  pthGrBrush.SetFocusScales(0.01f, 0.15f);
				}
				else if (ill.gettype() == 1)
					pthGrBrush.SetFocusScales(0.2f, 0.2f);
				else if (ill.gettype() == 1)
					pthGrBrush.SetFocusScales(0.001f, 0.001f);
				graphics.FillPolygon(&pthGrBrush, edges[i], 4);
			}
			else {
				Gdiplus::Pen pen(Gdiplus::Color(255, 255, 255, 255));
				graphics.DrawPolygon(&pen, edges[i], 4);
			}
	}
	ill.draw(hdc);

}