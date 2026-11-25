#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

int W = 800, H = 600;
int style = 1;
bool objectMode = false;

struct Point {
    int x, y;
};

struct Line {
    Point a, b;
};

vector<Line> lines;
vector<Point> objectPoints;

Point firstPoint;
bool waitingForSecond = false;

void plotPixel(int x, int y, float size) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2i(x + W / 2, H / 2 - y);
    glEnd();
}

void bresenham(int x1, int y1, int x2, int y2, int lineStyle) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;
    int step = 0;

    while (true) {
        bool draw = false;

        if (lineStyle == 1) {
            draw = true;
        } 
        else if (lineStyle == 2) {
            draw = (step % 4 == 0);
        } 
        else if (lineStyle == 3) {
            draw = (step % 12 < 8);
        } 
        else if (lineStyle == 4) {
            draw = true;
        }

        if (draw) {
            float size = (lineStyle == 4) ? 3.0f : 1.0f;
            plotPixel(x1, y1, size);
        }

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }

        step++;
    }
}

void drawAxes() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(1);

    glBegin(GL_LINES);

    // X-axis
    glVertex2i(0, H / 2);
    glVertex2i(W, H / 2);

    // Y-axis
    glVertex2i(W / 2, 0);
    glVertex2i(W / 2, H);

    glEnd();

    glColor3f(0, 0, 1);

    // Origin
    glRasterPos2i(W / 2 + 10, H / 2 - 20);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'O');

    // Quadrant labels
    glRasterPos2i(W * 3 / 4, H / 4);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'I');

    glRasterPos2i(W / 4, H / 4);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'I');

    glRasterPos2i(W / 4, H * 3 / 4);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'I');

    glRasterPos2i(W * 3 / 4, H * 3 / 4);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'I');
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    // Draw lines
    glColor3f(1, 0, 0);

    for (const auto &line : lines) {
        bresenham(
            line.a.x,
            line.a.y,
            line.b.x,
            line.b.y,
            style
        );
    }

    glColor3f(0, 0.6f, 0);

    for (const auto &p : objectPoints) {
        plotPixel(p.x, p.y, 6);
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) {
        return;
    }

    Point p;
    p.x = x - W / 2;
    p.y = H / 2 - y;

    if (objectMode) {
        if (!objectPoints.empty()) {
            Point previous = objectPoints.back();
            lines.push_back({previous, p});
        }

        objectPoints.push_back(p);
    } 
    else {
        if (!waitingForSecond) {
            firstPoint = p;
            waitingForSecond = true;

            cout << "Start point: ("
                 << p.x << ", " << p.y << ")\n";
        } 
        else {
            lines.push_back({firstPoint, p});
            waitingForSecond = false;

            cout << "End point: ("
                 << p.x << ", " << p.y << ")\n";
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '4') {
        style = key - '0';
        cout << "Line style: " << style << endl;
    }

    if (key == 'o' || key == 'O') {
        objectMode = !objectMode;
        waitingForSecond = false;

        cout << (objectMode
                     ? "Object mode ON\n"
                     : "Object mode OFF\n");
    }

    if (key == 'c' || key == 'C') {
        lines.clear();
        objectPoints.clear();
        waitingForSecond = false;
    }

    if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }

    glutPostRedisplay();
}

void reshape(int w, int h) {
    W = w;
    H = h;

    glViewport(0, 0, W, H);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, H, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Bresenham Line Drawing");

    glClearColor(1, 1, 1, 1);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    cout << "\nBRESENHAM LINE DRAWING\n";
    cout << "1 - Simple line\n";
    cout << "2 - Dotted line\n";
    cout << "3 - Dashed line\n";
    cout << "4 - Solid thick line\n";
    cout << "O - Toggle object drawing mode\n";
    cout << "C - Clear screen\n";
    cout << "Q - Quit\n";
    cout << "Click two points to draw a line.\n";

    glutMainLoop();

    return 0;
}