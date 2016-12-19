#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "Matrix.h"
#include "Utils.h"
#include "Cube.h"
#define pi 3.14159265359

GLsizei winWidth = 800, winHeight = 600;

GLint keyStates[256];

double r = 3;
double t = 0;
double m = 0;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
}

void keyOperations()
{

    if (keyStates['w'])
    {
        if (m < 15)
        {
            m += 0.01;
        }
        //   printf("%f\n", m);
    }

    if (keyStates['s'])
    {
        if (m > -15)
        {
            m -= 0.01;
        }
        // printf("%f\n", m);
    }

    if (keyStates['a'])
    {
        t += 0.01;
        // std::cout << angle << std::endl;
    }

    if (keyStates['d'])
    {

        t -= 0.01;
        //std::cout << angle << std::endl;
    }

    if (keyStates['y'])
    {
        if(r < 15)
        r += 0.01;
        //std::cout << angle << std::endl;
    }

    if (keyStates['x'])
    {
        if( r > 5)
        r -= 0.01;
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

    cube1 = Cube(Vector(0, 0, 0), 0.0, 1.0, 1.0);
    cube2 = Cube(Vector(2, 0, 0), 0.545, 0.271, 0.075);
    cube3 = Cube(Vector(-2, 0, 0), 1.0, 0.0, 0.0);

    cube4 = Cube(Vector(0, -2, 0), 0.0, 1.0, 0.0);
    cube5 = Cube(Vector(0, 2, 0), 0.0, 0.0, 1.0);
    cube6 = Cube(Vector(0, 0, 2), 0.184, 0.310, 0.310);
    cube7 = Cube(Vector(0, 0, -2), 0.0, 0.502, 0.0);


    Matrix WTV = Matrix::calcWTV(-4, 4, -4, 4, 100, 500, 100, 500);
    Matrix centralisVet = Matrix::getCentralisMatrix(4, 4, 3);

    Vector up = Vector(0, 0, 1);

    Vector c = Vector(r * cos(t), r * sin(t), m);
    Vector target = Vector(0, 0, 0);

    Matrix K = Matrix::getCameraMatrix(up, c, target);

    // K.display();
    //printf("\n");

    Matrix tmp;// = K;
    // cube1.print();

   // cube1.transform(tmp);
    
    tmp = WTV * (centralisVet* K);

    cube1.transform(tmp);
    cube1.refreshVectors();
    
   // cube1.printLapVector();

  /*  cube2.transform(tmp);
    cube3.transform(tmp);
    cube4.transform(tmp);
    cube5.transform(tmp);
    cube6.transform(tmp);
    cube7.transform(tmp);*/

    cube1.draw();
   /* cube2.draw();
    cube3.draw();
    cube4.draw();
    cube5.draw();
    cube6.draw();
    cube7.draw();*/

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