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
        Matrix(4,4);
    }

    Matrix(int n, int m)
    {
        this->n = n;
        this->m = m;

        data = new double *[n];
        for (int i = 0; i < n; i++){
            data[i] = new double[m];
        }

          for (int i = 0; i < n; i++){
              for(int j=0; j<m; j++)
               data[i][j] =0;
        }


        
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

        Matrix ret = Matrix(4, 4);
        float sum;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                sum = 0;
                for (int k = 0; k < 4; k++)
                    sum = sum + this->data[i][k] * Other.data[k][j];
                ret.data[i][j] = sum;
            }

        return ret;
    }
    static Matrix getEltoltasMatrix(double u, double v, double w){
        std::vector<std::vector<double>> tmp2 = {{1, 0, 0, u},
                                                {0, 1, 0, v},
                                                {0, 0, 1, w},
                                                {0, 0, 0, 1}};
        return Matrix(4, 4, tmp2);

    }
    static Matrix getSkalazasMatrix(double u, double v, double w){
        std::vector<std::vector<double>> tmp = {{u, 0, 0, 0},
                                                {0, u, 0, 0},
                                                {0, 0, w, 0},
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
                                                {0, 0, -1.0/s, 1}};

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

        Vector w;
        w.x = c.x - p.x;
        w.y = c.y - p.y;
        w.z = c.z - p.z;

        w.x *= -1;
        w.y *= -1;
        w.z *= -1;

        double h = w.length();

        w.x = w.x / h;
        w.y = w.y / h;
        w.z = w.z / h;

        
        Vector u = Vector::getVectorialMul(up, w);
        h = u.length();
        u.x = u.x /  h; 
        u.y = u.y /  h;
        u.z = u.z /  h;


        Vector v = Vector::getVectorialMul(w, u);
        h = v.length();

        v.x = v.x /h ;
        v.y = v.y /h ;
        v.z = v.z /h ;

      std::vector<std::vector<double>> tmp = {  {u.x,   u.y, u.z, -Vector::getSkalarWithVector(c, u)},
                                                {v.x,   v.y, v.z, -Vector::getSkalarWithVector(c, v)},
                                                {w.x,   w.y, w.z, -Vector::getSkalarWithVector(c, w)},
                                                {0,     0,   0,     1}};


   /* double x[4][4]= {  {u.x,   u.y, u.z, -Vector::getSkalarWithVector(c, u)},
                                                {v.x,   v.y, v.z, -Vector::getSkalarWithVector(c, v)},
                                                {w.x,   w.y, w.z, -Vector::getSkalarWithVector(c, w)},
                                                {0,     0,   0,     1}};
    Matrix s = Matrix(4,4);
    
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                s.data[i][j] = x[i][j];
*/

       return Matrix(4,4, tmp); 


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
