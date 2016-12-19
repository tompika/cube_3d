/**
    
    Matrix.h
    Bevgraf - 3. hazi

    @author Péter Szilvácsku
    @version 1.0 2016.11.10. 
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include "Vector.h"
#define pi 3.14159265359

class Matrix
{

  public:
    double **data;
    int m, n;

    Matrix()
    {
    }

    Matrix(int n, int m)
    {
        this->n = n;
        this->m = m;

        data = new double *[n];
        for (int i = 0; i < n; i++)
            data[i] = new double[m];
    }

    Matrix(int n, int m, std::vector<std::vector<double>> data_)
    {
        this->n = n;
        this->m = m;
        data = new double *[n];
        for (int i = 0; i < n; i++)
            data[i] = new double[m];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                data[i][j] = data_[i][j];
            }
        }
    }

    Matrix operator*(const Matrix Other)
    {

        Matrix ret = Matrix(n, Other.m);
        float sum;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < Other.m; j++)
            {
                sum = 0;
                for (int k = 0; k < m; k++)
                    sum = sum + this->data[i][k] * Other.data[k][j];
                ret.data[i][j] = sum;
            }

        return ret;
    }
    static Matrix getEltoltasMatrix(double u, double v, double w){
        std::vector<std::vector<double>> tmp = {{1, 0, 0, u},
                                                {0, 1, 0, v},
                                                {0, 0, 1, w},
                                                {0, 0, 0, 1}};
        return Matrix(4, 4, tmp);

    }

    static Matrix getRotationMatrixX(int n, int m, double angle)
    {

        double rad = angle * (pi / 180);
        std::vector<std::vector<double>> tmp = {{1, 0, 0, 0},
                                                {0, cos(rad), -sin(rad), 0},
                                                {0, sin(rad), cos(rad), 0},
                                                {0, 0, 0, 1}};
        return Matrix(n, m, tmp);
    }

    static Matrix getRotationMatrixY(int n, int m, double angle)
    {

        double rad = angle * (pi / 180);

        std::vector<std::vector<double>> tmp = {{cos(rad), 0, sin(rad), 0},
                                                {0, 1, 0, 0},
                                                {-sin(rad), 0, cos(rad), 0},
                                                {0, 0, 0, 1}};
        return Matrix(n, m, tmp);
    }


    static Matrix getMerolegesMatrix(int n, int m){
        std::vector<std::vector<double>> tmp = {{1, 0, 0, 0},
                                                {0, 1, 0, 0},
                                                {0, 0, 0, 0},
                                                {0, 0, 0, 1}};

        return Matrix(n, m, tmp);


    }
    static Matrix getCentralisMatrix(int n, int m, double s){
          std::vector<std::vector<double>> tmp = {{1, 0, 0, 0},
                                                {0, 1, 0, 0},
                                                {0, 0, 0, 0},
                                                {0, 0, -1/s, 1}};

        return Matrix(n, m, tmp);

    }
    static Matrix calcWTV(double x_min, double x_max, double y_min, double y_max, double u_min, double u_max, double v_min, double v_max)
    {

           std::vector<std::vector<double>> WT = { {(u_max - u_min) / (x_max - x_min),      0,  0, u_min-x_min *((u_max - u_min) / (x_max - x_min)) },
                                                    {0,     (v_max - v_min) / (y_max - y_min),  0,  v_min-y_min *((v_max - v_min) / (y_max - y_min)) },
                                                    {0,     0,              1, 0},
                                                    {0,     0,              0, 1}};


        Matrix VTW = Matrix(4,4, WT);

  
  
   
        return VTW;

    }

    static Matrix getCameraMatrix(Vector up, Vector c, Vector p){


       
        Vector pc = c - p;
        Vector w;

        w.x = pc.x / pc.length();
        w.y = pc.y / pc.length();
        w.z = pc.z / pc.length();
         

        Vector u = Vector::getVectorialMul(up, w); 

        u.x = u.x /  u.length(); 
        u.y = u.y /  u.length();
        u.z = u.z /  u.length();


        Vector v = Vector::getVectorialMul(w, u);

        v.x = v.x / v.length() ;
        v.y = v.y / v.length() ;
        v.z = v.z / v.length() ;


        /*std::cout << "v : ";
            v.print();*/



      std::vector<std::vector<double>> tmp = {  {u.x,   u.y, u.z, -Vector::getSkalarWithVector(c, u)},
                                                {v.x,   v.y, v.z, -Vector::getSkalarWithVector(c, v)},
                                                {w.x,   w.y, w.z, -Vector::getSkalarWithVector(c, w)},
                                                {0,     0,   0,     1}};



       return Matrix(4, 4, tmp); 
    }


    void display()
    {

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

#endif
