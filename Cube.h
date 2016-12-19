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

    std::vector<Vector> lapVectors;
    std::vector<Point3D> points;
    double r;
    double g;
    double b;
    int s = 3;
    double flag1, flag2, flag3, flag4, flag5, flag6;

    Cube()
    {
    }

    Cube(Vector pos, double r_, double g_, double b_)
    {
        this->r = r_;
        this->g = g_;
        this->b = b_;

        Point3D c0, c1, c2, c3, c4, c5, c6, c7;
        std::vector<Point3D> point;

        c0 = initPoint3D(0.5, -0.5, -0.5);
        c1 = initPoint3D(0.5, 0.5, -0.5);
        c2 = initPoint3D(-0.5, 0.5, -0.5);
        c3 = initPoint3D(-0.5, -0.5, -0.5);

        c4 = initPoint3D(0.5, -0.5, 0.5);
        c5 = initPoint3D(0.5, 0.5, 0.5);
        c6 = initPoint3D(-0.5, 0.5, 0.5);
        c7 = initPoint3D(-0.5, -0.5, 0.5);

        point.push_back(c0);
        point.push_back(c1);
        point.push_back(c2);
        point.push_back(c3);

        point.push_back(c4);
        point.push_back(c5);
        point.push_back(c6);
        point.push_back(c7);

        this->points = point;

        transform(Matrix::getEltoltasMatrix(pos.x, pos.y, pos.z));
        calcLapCenterPoint();
        calcVectors();
    
    }
    void calcVectors()
    {
        lapVectors.clear();
        Vector tmp;
        Vector tmp2;
        int i, j;
        i = 0;
        j = 1;
        //01
        tmp = Vector(points[i].x, points[i].y, points[i].z) - Vector(lalso.x, lalso.y, lalso.z);
        tmp2 = Vector(points[1].x, points[1].y, points[1].z) - Vector(lalso.x, lalso.y, lalso.z);

        lapVectors.push_back(Vector::getVectorialMul(tmp, tmp2));
        //45
        i = 4;
        j = 5;
        tmp = Vector(points[i].x, points[i].y, points[i].z) - Vector(lfelso.x, lfelso.y, lfelso.z);
        tmp2 = Vector(points[j].x, points[j].y, points[j].z) - Vector(lfelso.x, lfelso.y, lfelso.z);

        lapVectors.push_back(Vector(Vector::getVectorialMul(tmp, tmp2)));
        //65
        i = 6;
        j = 5;
        tmp = Vector(points[i].x, points[i].y, points[i].z) - Vector(lhatul.x, lhatul.y, lhatul.z);
        tmp2 = Vector(points[j].x, points[j].y, points[j].z) - Vector(lhatul.x, lhatul.y, lhatul.z);

        lapVectors.push_back(Vector(Vector::getVectorialMul(tmp, tmp2)));
        //74
        i = 7;
        j = 4;
        tmp = Vector(points[i].x, points[i].y, points[i].z) - Vector(lelol.x, lelol.y, lelol.z);
        tmp2 = Vector(points[j].x, points[j].y, points[j].z) - Vector(lelol.x, lelol.y, lelol.z);

        lapVectors.push_back(Vector(Vector::getVectorialMul(tmp, tmp2)));
        //67
        i = 6;
        j = 7;
        tmp = Vector(points[i].x, points[i].y, points[i].z) - Vector(lbal.x, lbal.y, lbal.z);
        tmp2 = Vector(points[j].x, points[j].y, points[j].z) - Vector(lbal.x, lbal.y, lbal.z);

        lapVectors.push_back(Vector(Vector::getVectorialMul(tmp, tmp2)));
        //01
        i = 0;
        j = 1;
        tmp = Vector(points[i].x, points[i].y, points[i].z) - Vector(ljobb.x, ljobb.y, ljobb.z);
        tmp2 = Vector(points[j].x, points[j].y, points[j].z) - Vector(ljobb.x, ljobb.y, ljobb.z);

        lapVectors.push_back(Vector(Vector::getVectorialMul(tmp, tmp2)));
    }

    void setFlags(){
        Vector p = Vector(points[4].x, points[4].y, points[4].z);
        Vector c = Vector(0,0, s);
        Vector PC = c - p;

        flag1 = Vector::getSkalarWithVector(PC, lapVectors[1]);
     
        

          p = Vector(points[0].x, points[0].y, points[0].z);
        PC = c - p;
        flag2 = Vector::getSkalarWithVector(PC, lapVectors[0]);


        p = Vector(points[2].x, points[2].y, points[2].z);
        PC = c - p;
        flag3 = Vector::getSkalarWithVector(PC, lapVectors[4]);
      

             p = Vector(points[0].x, points[0].y, points[0].z);
        PC = c - p;
        flag4 = Vector::getSkalarWithVector(PC, lapVectors[3]);
    



    }

    void calcLapCenterPoint()
    {

        double x = 0, y = 0, z = 0;
        for (int i = 0; i < 4; i++)
        {
            x += points[i].x;
            y += points[i].y;
            z += points[i].z;
        }
        lalso.x = x / 4;
        lalso.y = y / 4;
        lalso.z = z / 4;

        x = y = z = 0;

        for (int i = 4; i < 8; i++)
        {
            x += points[i].x;
            y += points[i].y;
            z += points[i].z;
        }
        lfelso.x = x / 4;
        lfelso.y = y / 4;
        lfelso.z = z / 4;

        ////////////////////
        //2, 3, 6, 7 baloldal
        x = y = z = 0;
        x += points[2].x + points[3].x + points[6].x + points[7].x;
        y += points[2].y + points[3].y + points[6].y + points[7].y;
        z += points[2].z + points[3].z + points[6].y + points[7].z;

        lbal.x = x / 4;
        lbal.y = y / 4;
        lbal.z = z / 4;
        /////////////////////
        //0,3,7,4 elülső
        x = y = z = 0;

        x += points[0].x + points[3].x + points[7].x + points[4].x;
        y += points[0].y + points[3].y + points[7].y + points[4].y;
        z += points[0].z + points[3].z + points[7].z + points[4].z;

        lelol.x = x / 4;
        lelol.y = y / 4;
        lelol.z = z / 4;
        /////////////////
        // 0 1 5 4 jobb oldal
        x = y = z = 0;

        x += points[0].x + points[1].x + points[5].x + points[4].x;
        y += points[0].y + points[1].y + points[5].y + points[4].y;
        z += points[0].z + points[1].z + points[5].z + points[4].z;

        ljobb.x = x / 4;
        ljobb.y = y / 4;
        ljobb.z = z / 4;

        /////////////////
        // 1 2 6 5 hátsó
        x = y = z = 0;

        x += points[1].x + points[2].x + points[6].x + points[5].x;
        y += points[1].y + points[2].y + points[6].y + points[5].y;
        z += points[1].z + points[2].z + points[6].z + points[5].z;

        lhatul.x = x / 4;
        lhatul.y = y / 4;
        lhatul.z = z / 4;
    }

    void transform(Matrix M)
    {

        //  std::cout << "(" <<M.n << " " << M.m << ")" <<std::endl;

        int i, j, k;
        for (i = 0; i < points.size(); i++)
        {

            float tmp[4] = {points[i].x, points[i].y, points[i].z, 1};
            float res[M.n];
            //std::cout <<tmp[0] <<" " <<tmp[1] << " " <<tmp[2] << " " << tmp[3] << std::endl;

            for (j = 0; j < M.n; j++)
            {
                res[j] = 0;
                for (k = 0; k < M.m; k++)
                    res[j] += M.data[j][k] * tmp[k];
            }

            // std::cout <<res[0] <<" " <<res[1] << " " <<res[2] << " " << res[3] << std::endl;
            //std::cout << M.n << std::endl;

            points[i].x = res[0] / res[M.n - 1];
            points[i].y = res[1] / res[M.n - 1];
        }
    }

    void refreshVectors(){
        calcLapCenterPoint();
        calcVectors();
    }

    void printLapVector(){

        for(int i=0; i<lapVectors.size(); i++){
            printf("%f %f %f\n", lapVectors[i].x,  lapVectors[i].y,  lapVectors[i].z);
        }
        std::cout << std::endl;
    }

    void print()
    {

        for (int i = 0; i < points.size(); i++)
            std::cout << "x= " << points[i].x << " y= " << points[i].y << " z= " << points[i].z << std::endl;
    }

    void draw()
    {

        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        //2      1
        //
        //
        //3      0

        glVertex2f(points[0].x, points[0].y);
        glVertex2f(points[1].x, points[1].y);

        glVertex2f(points[1].x, points[1].y);
        glVertex2f(points[2].x, points[2].y);

        glVertex2f(points[2].x, points[2].y);
        glVertex2f(points[3].x, points[3].y);

        glVertex2f(points[3].x, points[3].y);
        glVertex2f(points[0].x, points[0].y);

        glEnd();
        glBegin(GL_LINES);

        ////
        //6      5
        //
        //
        //7      4
        glVertex2f(points[4].x, points[4].y);
        glVertex2f(points[5].x, points[5].y);

        glVertex2f(points[5].x, points[5].y);
        glVertex2f(points[6].x, points[6].y);

        glVertex2f(points[6].x, points[6].y);
        glVertex2f(points[7].x, points[7].y);

        glVertex2f(points[7].x, points[7].y);
        glVertex2f(points[4].x, points[4].y);

        ////
        //62      51
        //
        //
        //73      40
        glVertex2f(points[4].x, points[4].y);
        glVertex2f(points[0].x, points[0].y);

        glVertex2f(points[5].x, points[5].y);
        glVertex2f(points[1].x, points[1].y);

        glVertex2f(points[6].x, points[6].y);
        glVertex2f(points[2].x, points[2].y);

        glVertex2f(points[7].x, points[7].y);
        glVertex2f(points[3].x, points[3].y);

        glEnd();

        ///LAPOK
        glColor3f(r, g, b);

        //felső
     

        if( flag1 >= 0.0){ 
            glBegin(GL_POLYGON);
            glVertex2f(points[4].x, points[4].y);
            glVertex2f(points[5].x, points[5].y);
            glVertex2f(points[6].x, points[6].y);
            glVertex2f(points[7].x, points[7].y);   
            glEnd();
        }
        
        ///////
        //alsó


        if( flag2 >= 0.0){
            glBegin(GL_POLYGON);
            glVertex2f(points[0].x, points[0].y);
            glVertex2f(points[1].x, points[1].y);
            glVertex2f(points[2].x, points[2].y);
            glVertex2f(points[3].x, points[3].y);
            glEnd();
        }

        ///////////
        //bal oldali

        
        if( flag3 >= 0.0){
            glBegin(GL_POLYGON);
            glVertex2f(points[2].x, points[2].y);
            glVertex2f(points[3].x, points[3].y);
            glVertex2f(points[7].x, points[7].y);
            glVertex2f(points[6].x, points[6].y);
            glEnd();
        }


        //////////
        //szemben lévő
      
         if( flag4 >= 0.0){   
        glBegin(GL_POLYGON);
        glVertex2f(points[0].x, points[0].y);
        glVertex2f(points[3].x, points[3].y);
        glVertex2f(points[7].x, points[7].y);
        glVertex2f(points[4].x, points[4].y);
        glEnd();
         }

         //
        //jobb oldali
        if( flag5 >= 0.0){
        glBegin(GL_POLYGON);
        glVertex2f(points[0].x, points[0].y);
        glVertex2f(points[1].x, points[1].y);
        glVertex2f(points[5].x, points[5].y);
        glVertex2f(points[4].x, points[4].y);
        glEnd();
        }

        //hátsó
              if( flag5 >= 0.0){
        glBegin(GL_POLYGON);
        glVertex2f(points[1].x, points[1].y);
        glVertex2f(points[2].x, points[2].y);
        glVertex2f(points[6].x, points[5].y);
        glVertex2f(points[5].x, points[6].y);
        glEnd();
        }
    }
};

#endif
