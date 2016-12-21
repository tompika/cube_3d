/**
    
    Cube.h
    Bevgraf - 6. hazi

    @author Péter Szilvácsku
    @version 1.0 2016.12.12. 
*/

#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include "Utils.h"
#include "Matrix.h"
#include "Vector.h"
#include "Lap.h"

class Cube
{

  public:
    Vector center;

    Point3D lalso;
    Point3D lfelso;
    Point3D lbal;
    Point3D ljobb;
    Point3D lelol;
    Point3D lhatul;

    Vector vec_also;
    Vector vec_felso;
    Vector vec_bal;
    Vector vec_jobb;
    Vector vec_elol;
    Vector vec_hatul;

    std::vector<Lap> laps;
    std::vector<Point3D> points;
    double r;
    double g;
    double b;
    int s = 4;

    GLint lapok[6][4] = {{0, 1, 2, 3},
                         {3, 2, 6, 7},
                         {7, 6, 5, 4},
                         {4, 5, 1, 0},
                         {4, 0, 3, 7},
                         {1, 5, 6, 2}};

    Cube()
    {
    }

    Cube(Vector pos, double r_, double g_, double b_, Matrix K, Matrix M)
    {

        // M.display();

        this->r = r_;
        this->g = g_;
        this->b = b_;

        Point3D c0, c1, c2, c3, c4, c5, c6, c7;
        std::vector<Point3D> point;
        std::vector<Point3D> point_default;
        std::vector<Lap> lap_default;
        /*
	            -0.5f,	0.5f,	0.5f,
				-0.5f,	-0.5f,	0.5f,
				0.5f,	-0.5f,	0.5f,
				0.5f,	0.5f,	0.5f,
                            
				-0.5f,	0.5f,	-0.5f,
				-0.5f,	-0.5f,	-0.5f,
				0.5f,	-0.5f,	-0.5f,
				0.5f,	0.5f,	-0.5f,*/

        c0 = initPoint3D(-0.5, 0.5, 0.5);
        c1 = initPoint3D(-0.5, -0.5, 0.5);
        c2 = initPoint3D(0.5, -0.5, 0.5);
        c3 = initPoint3D(0.5, 0.5, 0.5);

        c4 = initPoint3D(-0.5, 0.5, -0.5);
        c5 = initPoint3D(-0.5, -0.5, -0.5);
        c6 = initPoint3D(0.5, -0.5, -0.5);
        c7 = initPoint3D(0.5, 0.5, -0.5);

        point.push_back(c0);
        point.push_back(c1);
        point.push_back(c2);
        point.push_back(c3);

        point.push_back(c4);
        point.push_back(c5);
        point.push_back(c6);
        point.push_back(c7);

        this->points = point;

        /////////////////////
        std::vector<Point3D> t;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                t.push_back(points[lapok[i][j]]);
            }
            laps.push_back(Lap(t, r, g, b));
            t.clear();
        }

        transform(Matrix::getEltoltasMatrix(pos.x, pos.y, pos.z));

        ////////////////////

        transform(K);

        for (int i = 0; i < laps.size(); i++)
            laps[i].refresh();

        calcDropLap();

        transform(M);
    }

    void calcDropLap()
    {

        Vector p;
        Vector c = Vector(0, 0, s);
        Vector PC;
        double flag;
        for (int i = 0; i < laps.size(); i++)
        {
            p = Vector(laps[i].p[0].x, laps[i].p[0].y, laps[i].p[0].z);

            PC.x = c.x - p.x;
            PC.y = c.y - p.y;
            PC.z = c.z - p.z;

            flag = Vector::getSkalarWithVector(PC, laps[i].norm);

            if (flag < 0)
            {
                laps.erase(laps.begin() + i);
            }
        }
    }

    void transform(Matrix M)
    {

        // std::cout << "(" <<M.n << " " << M.m << ")" <<std::endl;

        int i, j, k, l;

        for (int i = 0; i < laps.size(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float tmp[4] = {laps[i].p[j].x, laps[i].p[j].y, laps[i].p[j].z, 1};
                float res[4];

                for (k = 0; k < 4; k++)
                {
                    res[k] = 0;
                    for (l = 0; l < 4; l++)
                        res[k] += M.data[k][l] * tmp[l];
                }

                laps[i].p[j].x = res[0] / res[3];
                laps[i].p[j].y = res[1] / res[3];
                laps[i].p[j].z = res[2] / res[3];
            }
        }
    }

    void refreshVectors()
    {
        calcLapCenterPoint();
        calcNormalVectors();
    }

    void print()
    {

        for (int i = 0; i < points.size(); i++)
            std::cout << "x= " << points[i].x << " y= " << points[i].y << " z= " << points[i].z << std::endl;
    }

    void draw()
    {
    }
};

#endif
