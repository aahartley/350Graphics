#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();

}
void init() {
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

int main() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(400,150);
	glutCreateWindow("Example");

	glutDisplayFunc(display);
	init();

	glutMainLoop();

	return 0;
}