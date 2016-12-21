#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <algorithm>

#include "Matrix.h"
#include "Utils.h"
#include "Cube.h"
#define pi 3.14159265359

GLsizei winWidth = 800, winHeight = 600;

GLint keyStates[256];

std::vector<Lap> lapook;
std::vector<Cube> kockak;

double r = 15;
double t = 0;
double m = 0;

Vector up = Vector(0, 0, 1);
Vector p = Vector(0, 0, 0);
Vector c = Vector(r * cos(t), r *sin(t), m);





Matrix WTV = Matrix::calcWTV(-1, 1, -1, 1, 0, 600, 0, 600);
Matrix centralisVet = Matrix::getCentralisMatrix(4, 4, 4);

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);


}

bool compareLap(Lap a, Lap b)
{

    return a.getDistanceFromCentrum() > b.getDistanceFromCentrum();
}

void keyOperations()
{

    if (keyStates['w'])
    {
        if (m < 15)
        {
            m += 0.01;
            c.z = m;
        }
        //   printf("%f\n", m);
    }

    if (keyStates['s'])
    {
        if (m > -15)
        {
            m -= 0.01;
            c.z = m;
        }
        // printf("%f\n", m);
    }

    if (keyStates['a'])
    {
        t += 0.1;
        c.x = r * cos(t);
        c.y = r * sin(t);
    }

    if (keyStates['d'])
    {

        t -= 0.1;
        c.x = r * cos(t);
        c.y = r * sin(t);
    }

    if (keyStates['y'])
    {
        if (r < 20){
            r += 0.1;
        c.x = r * cos(t);
        c.y = r * sin(t);
        }
    }

    if (keyStates['x'])
    {
        if (r > 10){
            r -= 0.1;
        c.x = r * cos(t);
        c.y = r * sin(t);
        }
    }

    glutPostRedisplay();
}

void display()
{
    keyOperations();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    Cube cube1;
    Cube cube2;
    Cube cube3;
    Cube cube4;
    Cube cube5;
    Cube cube6;
    Cube cube7;

    Matrix K = Matrix::getCameraMatrix(up, c, p);
    Matrix N = WTV * centralisVet; 


    cube1 = Cube(Vector(0, 0, 0), 0.0, 1.0, 1.0, K, N);
    cube2 = Cube(Vector(2, 0, 0), 0.545, 0.271, 0.075, K, N);
    cube3 = Cube(Vector(-2, 0, 0), 1.0, 0.0, 0.0, K, N);

    cube4 = Cube(Vector(0, -2, 0), 0.0, 1.0, 0.0, K, N);
    cube5 = Cube(Vector(0, 2, 0), 0.0, 0.0, 1.0, K, N);

    cube6 = Cube(Vector(0, 0, 2), 0.184, 0.310, 0.310, K, N);
    cube7 = Cube(Vector(0, 0, -2), 0.0, 0.502, 0.0, K, N);

    kockak.push_back(cube1);
    kockak.push_back(cube2);
    kockak.push_back(cube3);
    kockak.push_back(cube4);
    kockak.push_back(cube5);
    kockak.push_back(cube6);
    kockak.push_back(cube7);

    for (int i = 0; i < kockak.size(); i++)
    {
        for (int j = 0; j < kockak[i].laps.size(); j++)
            lapook.push_back(kockak[i].laps[j]);
    }

    std::sort(lapook.begin(), lapook.end(), compareLap);

    for (int i = 0; i < lapook.size(); i++)
    {
        lapook[i].draw();
    }
  

    kockak.clear();
    lapook.clear();


    glutSwapBuffers();
}

/*void update(int n)
{
    


    glutPostRedisplay();

    glutTimerFunc(5, update, 0);
}*/

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = 0;
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("Cubes");
    init();

    glutDisplayFunc(display);

    //   glutMouseFunc(processMouse);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    // glutTimerFunc(5, update, 0);

    glutMainLoop();
    return 0;
}