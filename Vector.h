/**
    
    Vector.h
    Bevgraf - 6. hazi

    @author Péter Szilvácsku
    @version 1.0 2016.12.12. 
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

class Vector
{
  public:
    double x;
    double y;
    double z;

    Vector()
    {
        Vector(0.0, 0.0, 0.0);
    }

    Vector(double X, double Y, double Z)
    {

        this->x = X;
        this->y = Y;
        this->z = Z;
    }

    /*************************************************/

    Vector operator+(const Vector v)
    {

        return Vector(x + v.x,
                      y + v.y,
                      z + v.z);
    }

    Vector operator-(const Vector v)
    {

        return Vector(x - v.x,
                      y - v.y,
                      z - v.z);
    }

    Vector operator*(const Vector v)
    {

        return Vector(x * v.x,
                      y * v.y,
                      z * v.z);
    }

    Vector operator*(const double s)
    {

        return Vector(x * s,
                      y * s,
                      z * s);
    }

    Vector operator+(const double s)
    {

        return Vector(x + s,
                      y + s,
                      z + s);
    }

    Vector operator/(const double s)
    {

        return Vector(x / s,
                      y / s,
                      z / s);
    }

    static double getSkalarWithVector(const Vector v, const Vector v2)
    {

        return (v.x * v2.x) + (v.y * v2.y) + (v.z * v2.z);
    }

    static Vector getVectorialMul(const Vector v, const Vector v2)
    {
        Vector res;

        res.x = v.y * v2.z - v.z * v2.y;
        res.y = v.z * v2.x - v.x * v2.z;
        res.z = v.x * v2.y - v.y * v2.x;

        return res;
    }

    double length()
    {

        return std::sqrt(x * x + y * y + z * z);
    }
    void print()
    {

        std::cout << "( " << x << " " << y << " " << z << " )" << std::endl;
    }
};

#endif