/**
    
    Vector.h
    Bevgraf - 6. hazi

    @author Péter Szilvácsku
    @version 1.0 2016.12.12. 
*/

#ifndef LAP_H
#define LAP_H

#include <iostream>
#include <cmath>
#include "Vector.h"
class Lap
{
  public:
    std::vector<Point3D> p;

    Vector atlag;
    Vector norm;

    double r;
    double g;
    double b;

    Lap(std::vector<Point3D> p_, double r_, double g_, double b_)
    {
        this->r = r_;
        this->g = g_;
        this->b = b_;
        this->p = p_;
        this->atlag = this->calcAtlag();
        this->norm = this->calcNorm();
        
    }
    void refresh(){
        this->atlag = calcAtlag();
        this->norm = calcNorm();

    }

    Vector calcAtlag()
    {

        double x, y, z;
        x = y = z = 0;

        for (int i = 0; i < 4; i++)
        {
            x += p[i].x;
            y += p[i].y;
            z += p[i].z;
        }

        return Vector(x / 4, y / 4, z / 4);
    }

    Vector calcNorm()
    {
        Vector a = Vector(p[0].x, p[0].y, p[0].z) - Vector(atlag.x, atlag.y, atlag.z);
        Vector b = Vector(p[1].x, p[1].y, p[1].z) - Vector(atlag.x, atlag.y, atlag.z);

        return Vector::getVectorialMul(a, b);
    }

    double getDistanceFromCentrum()
    {

        Vector centrum = Vector(0, 0, 4);
        Vector center = atlag;

        return pow(center.x - centrum.x, 2) + pow(center.y - centrum.y, 2) + pow(center.z - centrum.z, 2);;
    }

    void draw()
    {


        glColor3f(r, g, b);

        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++)
        {
            glVertex2f(p[j].x, p[j].y);
        }
        glEnd();
    
        glLineWidth(1.0);

        glColor3f(0.0, 0.0, 0.0);

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 4; i++)
        {
            glVertex2f(p[i].x, p[i].y);
        }
        glEnd();
    }



};

#endif