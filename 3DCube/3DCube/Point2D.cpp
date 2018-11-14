#include "Point2D.h"


void Point2D::transformation(const double &teta, const double &phi) {
	x = (p3d.getx()*(-sin(teta)) + p3d.gety()*(cos(teta)) + RRRX);
	y = (p3d.getx()*(-cos(phi) * cos(teta)) - p3d.gety()*cos(phi) * sin(teta) + p3d.getz()*(sin(phi)) + RRRY);
}
