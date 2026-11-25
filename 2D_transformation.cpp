#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

int i;
const float PI = 3.14159265358979323846f;

float x[3] = {50, 150, 100};
float y[3] = {50, 50, 150};

float tx[3], ty[3];
int choice = 0;

float sx = 2, sy = 2;
float angle = 90;
float h = 50, k = 50;

void resetObject()
{
    for (int i = 0; i < 3; i++);
    {
        tx[i] = x[i];
        ty[i] = y[i];
    }
}

void scaling()
{
    for (int i = 0; i < 3; i++);
    {
        tx[i] = x[i] * sx;
        ty[i] = y[i] * sy;
    }
}

void rotation()
{
    float rad = angle * PI / 180.0f;

    for (int i = 0; i < 3; i++)
    {
        tx[i] = h + (x[i] - h) * cos(rad) - (y[i] - k) * sin(rad);
        ty[i] = k + (x[i] - h) * sin(rad) + (y[i] - k) * cos(rad);
    }
}

void reflection(int type)
{
    for (int i = 0; i < 3; i++)
    {
        if (type == 1)
        {
            tx[i] = x[i];
            ty[i] = -y[i];
        }
        else if (type == 2)
        {
            tx[i] = -x[i];
            ty[i] = y[i];
        }
        else if (type == 3)
        {
            tx[i] = -x[i];
            ty[i] = -y[i];
        }
        else if (type == 4)
        {
            tx[i] = y[i];
            ty[i] = x[i];
        }
    }
}

void drawAxes()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f(-350, 0);
    glVertex2f(350, 0);
    glVertex2f(0, -250);
    glVertex2f(0, 250);
    glEnd();
}

void drawTriangle(float px[], float py[], float r, float g, float b)
{
    glColor3f(r, g, b);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(px[i], py[i]);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawTriangle(x, y, 0.0f, 0.0f, 1.0f);
    if (choice != 0)
    {
        drawTriangle(tx, ty, 1.0f, 0.0f, 0.0f);
    }
    glFlush();
}

void menu(int option)
{
    choice = option;
    resetObject();

    switch (option)
    {
    case 1:
        cout << "Enter Sx and Sy: ";
        cin >> sx >> sy;
        scaling();
        break;
    case 2:
        cout << "Enter rotation angle: ";
        cin >> angle;
        cout << "Enter arbitrary point h and k: ";
        cin >> h >> k;
        rotation();
        break;
    case 3:
        reflection(1);
        break;
    case 4:
        reflection(2);
        break;
    case 5:
        reflection(3);
        break;
    case 6:
        reflection(4);
        break;
    case 7:
        choice = 0;
        break;
    case 8:
        exit(0);
    }

    if (choice >= 1 && choice <= 6)
    {
        cout << "\nTransformed vertices:\n";
        for (int i = 0; i < 3; i++)
        {
            cout << "(" << tx[i] << ", " << ty[i] << ")\n";
        }
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -250, 250);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 650);
    glutCreateWindow("2D Transformations");
    init();
    resetObject();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Scaling", 1);
    glutAddMenuEntry("Rotation about Arbitrary Point", 2);
    glutAddMenuEntry("Reflection about X-axis", 3);
    glutAddMenuEntry("Reflection about Y-axis", 4);
    glutAddMenuEntry("Reflection about Origin", 5);
    glutAddMenuEntry("Reflection about y=x", 6);
    glutAddMenuEntry("Reset", 7);
    glutAddMenuEntry("Exit", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    cout << "Right-click the graphics window" << " to select a transformation.\n";
    glutMainLoop();
    return 0;
}