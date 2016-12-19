
#ifndef UTILS_H
#define UTILS_H

typedef struct point2d
{
    GLdouble x, y;
} POINT2D;

/*typedef struct vector
{
    GLdouble x, y;
} Vector;*/

typedef struct point3d
{
    GLdouble x, y, z;
} Point3D;

typedef struct point3dhom
{
    GLfloat x, y, z, zz;
} Point3Dhom;

/****************************************/

Point3D initPoint3D(GLdouble x, GLdouble y, GLdouble z)
{
    Point3D P;
    P.x = x;
    P.y = y;
    P.z = z;
    return P;
}

Point3Dhom initHom(Point3D p)
{
    Point3Dhom P;
    P.x = p.x;
    P.y = p.y;
    P.z = p.z;
    P.zz = 1;

    return P;
}
/*
Vector initVector(GLdouble x, GLdouble y, GLdouble z)
{
    Vector P;
    P.x = x;
    P.y = y;
    P.z = z;
    return P;
}

POINT2D initPoint2D(GLdouble x, GLdouble y)
{
    POINT2D P;
    P.x = x;
    P.y = y;
    return P;
}*/

#endif