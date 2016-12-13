#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "Matrix.h"
#include "Utils.h"
#include "Cube.h"
#define pi 3.14159265359

GLsizei winWidth = 800, winHeight = 600;

GLint keyStates[256];

double r = 5;
double angle = 0;
double m = 2;

Cube cube1;
Cube cube2;
Cube cube3;
Cube cube4;
Cube cube5;
Cube cube6;
Cube cube7;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glPointSize(10.0);
}

void keyOperations()
{

    if (keyStates['w'])
    {
        if (m < 10)
            m += 0.01;
    }

    if (keyStates['s'])
    {
        if (m > -10)
            m -= 0.01;
    }

    if (keyStates['a'])
    {
        angle += 0.01;
       // std::cout << angle << std::endl;
    }

    if (keyStates['d'])
    {

        angle -= 0.01;
       // std::cout << angle << std::endl;
    }

    glutPostRedisplay();
}

void display()
{
    keyOperations();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    cube1 = Cube(Vector(0, 0, 0));
    cube2 = Cube(Vector(2, 0, 0));
    cube3 = Cube(Vector(-2, 0, 0));
    
    cube4 = Cube(Vector(0, -2, 0));
    cube5 = Cube(Vector(0, 2, 0));
    cube6 = Cube(Vector(0, 0, 2));
    cube7 = Cube(Vector(0, 0, -2));

    Matrix WTV = cube1.calcWTV(-1, 1, -1, 1, 0, 800, 0, 600);
    Matrix centralisVet = Matrix().getCentralisMatrix(4, 4, 2);

    Vector up = Vector(0, 0, 1);
    Vector c = Vector(r * cos(angle), r * sin(angle), m);
    Vector target = Vector(0, 0, 0);

    Matrix K = Matrix().getCameraMatrix(up, c, target);

    //  K.display();

    Matrix tmp = WTV * (centralisVet * K);

    cube1.transformH1(tmp);
    cube2.transformH1(tmp);
    cube3.transformH1(tmp);
    cube4.transformH1(tmp);
    cube5.transformH1(tmp);
    cube6.transformH1(tmp);
    cube7.transformH1(tmp);
    //cube1.h1.print();

    cube1.draw();
    cube2.draw();
    cube3.draw();
    cube4.draw();
    cube5.draw();
    cube6.draw();
    cube7.draw();
    

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

    glutCreateWindow("Cubes - Szilvacsku Peter");
    init();

    glutDisplayFunc(display);

    //   glutMouseFunc(processMouse);
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);

    // glutTimerFunc(5, update, 0);

    glutMainLoop();
    return 0;
}