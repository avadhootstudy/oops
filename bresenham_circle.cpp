#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

int W = 800, H = 600;

struct Circle {
int xc, yc, r;
};

vector<Circle> circles;

bool selectingCenter = true;
int centerX = 0, centerY = 0;
int previewX = 0, previewY = 0;
bool showPreview = false;

void plotPixel(int x, int y) {
glVertex2i(x + W / 2, H / 2 - y);
}

void plot8Points(int xc, int yc, int x, int y) {
glBegin(GL_POINTS);

plotPixel(xc + x, yc + y);
plotPixel(xc - x, yc + y);
plotPixel(xc + x, yc - y);
plotPixel(xc - x, yc - y);

plotPixel(xc + y, yc + x);
plotPixel(xc - y, yc + x);
plotPixel(xc + y, yc - x);
plotPixel(xc - y, yc - x);

glEnd();

}

void bresenhamCircle(int xc, int yc, int r) {
int x = 0;
int y = r;
int p = 3 - 2 * r;

while (x <= y) {
plot8Points(xc, yc, x, y);

x++;

if (p < 0) {
p = p + 4 * x + 6;
} else {
p = p + 4 * (x - y) + 10;
y--;
}
}
}

void drawAxes() {
glColor3f(0.65f, 0.65f, 0.65f);
glBegin(GL_LINES);

glVertex2i(0, H / 2);

glVertex2i(W, H / 2);

glVertex2i(W / 2, 0);
glVertex2i(W / 2, H);

glEnd();
}

void display() {
glClear(GL_COLOR_BUFFER_BIT);

drawAxes();

glColor3f(1.0f, 0.0f, 0.0f);

for (const auto &c : circles) {
bresenhamCircle(c.xc, c.yc, c.r);
}

if (showPreview && !selectingCenter) {
int dx = previewX - centerX;
int dy = previewY - centerY;
int r = (int)round(sqrt(dx * dx + dy * dy));

glColor3f(0.0f, 0.0f, 1.0f);
bresenhamCircle(centerX, centerY, r);

}

glFlush();
}

void mouse(int button, int state, int x, int y) {
if (button != GLUT_LEFT_BUTTON ||
state != GLUT_DOWN)
return;

int cx = x - W / 2;
int cy = H / 2 - y;

if (selectingCenter) {
centerX = cx;
centerY = cy;
selectingCenter = false;
showPreview = true;

cout << "Center: (" << centerX
<< ", " << centerY << ")\n";
} else {
int dx = cx - centerX;
int dy = cy - centerY;

int r = (int)round(sqrt(dx * dx + dy * dy));

if (r > 0) {
circles.push_back({centerX, centerY, r});

cout << "Radius: " << r << endl;
cout << "Circle drawn successfully.\n";
}

selectingCenter = true;
showPreview = false;
}

glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
if (key == 'c' || key == 'C') {
circles.clear();
selectingCenter = true;
showPreview = false;
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

glutCreateWindow("Bresenham Circle Drawing");

glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
glPointSize(2.0f);

glutDisplayFunc(display);
glutMouseFunc(mouse);

glutKeyboardFunc(keyboard);
glutReshapeFunc(reshape);

cout << "BRESENHAM CIRCLE DRAWING\n";
cout << "First click: Select center\n";
cout << "Second click: Set radius\n";
cout << "C: Clear all circles\n";
cout << "Q: Quit\n";

glutMainLoop();
return 0;
}