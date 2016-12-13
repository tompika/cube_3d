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
#include "Utils.h"
#include "Matrix.h"
#include "Hasab.h"

class Cube
{

  public:
    Hasab h1;
    Hasab h2;
    Hasab h3;

    Vector center;

    Cube(){
        Cube(Vector(0,0,0));
    }

    Cube(Vector pos)
    {


        Point3D c0, c1, c2, c3, c4, c5, c6, c7;

        std::vector<Point3D> point;


        c0 = initPoint3D(0.5, -0.5, -0.5);
        c1 = initPoint3D(0.5, 0.5, -0.5);
        c2 = initPoint3D(-0.5, 0.5, -0.5);
        c3 = initPoint3D(-0.5, -0.5, -0.5);

        point.push_back(c0);
        point.push_back(c1);
        point.push_back(c2);
        point.push_back(c3);

        c4 = initPoint3D(0.5, -0.5, 0.5);
        c5 = initPoint3D(0.5, 0.5, 0.5);
        c6 = initPoint3D(-0.5, 0.5, 0.5);
        c7 = initPoint3D(-0.5, -0.5, 0.5);
        point.push_back(c4);
        point.push_back(c5);
        point.push_back(c6);
        point.push_back(c7);

        for(int i=0; i< point.size(); i++){
            point[i].x += pos.x;
            point[i].y += pos.y;
            point[i].z += pos.z;
        }

    
        this->h1 = Hasab(point);

    }
    Matrix calcWTV(double x_min, double x_max, double y_min, double y_max, double u_min, double u_max, double v_min, double v_max)
    {

           std::vector<std::vector<double>> WT = { {(u_max - u_min) / (x_max - x_min),      0,  0, -x_min *((u_max - u_min) / (x_max - x_min))+u_min },
                                                    {0,     (v_max - v_min) / (y_max - y_min),  0,  -y_min *((v_max - v_min) / (y_max - y_min))+v_min },
                                                    {0,     0,              1, 0},
                                                    {0,     0,              0, 1}};


        Matrix VTW = Matrix(4,4, WT);

  
  
   
        return VTW;

    }
    void transformH1(Matrix M)
    {

      //  std::cout << "(" <<M.n << " " << M.m << ")" <<std::endl;

        
        for (int i = 0; i < h1.points.size(); i++)
        {

            float tmp[4] = {h1.points[i].x, h1.points[i].y, h1.points[i].z, 1};
            float res[M.n];
            //std::cout <<tmp[0] <<" " <<tmp[1] << " " <<tmp[2] << " " << tmp[3] << std::endl;
            
            for (int j = 0; j < M.n; j++)
            {   
                res[j] = 0;
                for (int k = 0; k < M.m; k++)
                    res[j] += M.data[j][k] * tmp[k];

            }
            

           // std::cout <<res[0] <<" " <<res[1] << " " <<res[2] << " " << res[3] << std::endl;
            //std::cout << M.n << std::endl;

            h1.points[i].x = res[0]/res[M.n-1];
            h1.points[i].y = res[1]/res[M.n-1];
        }
    }

   
    void draw()
    {
        h1.draw();
  
    }
};

#endif
