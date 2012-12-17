#ifndef CAL_POINT_H_INCLUDED
#define CAL_POINT_H_INCLUDED

struct point{
    double x;
    double y;
    double z;

    point(double xx = 0, double yy = 0, double zz = 0)
    : x(xx), y(yy), z(zz) {}
};

extern void down(point&);

#endif // CAL_POINT_H_INCLUDED
