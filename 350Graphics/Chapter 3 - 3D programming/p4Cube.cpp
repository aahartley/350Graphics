#include <GL/glut.h>

GLsizei ww = 512, wh = 512;

GLfloat vertices[8][3] = {{-1, -1, 1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1},
{-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1}};

GLfloat colors[8][3]= {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 0, 1},
{1, 0, 1}, {1, 1, 1}, {0, 1, 1}};

GLubyte cubeIndices[24] = {0, 3, 2, 1,		// face 0
							2, 3, 7, 6,		// face 1
							0, 4, 7, 3,		// face 2
							1, 2, 6, 5,		// face 3
							4, 5, 6, 7,		// face 4
							0, 1, 5, 4};	// face 5


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glShadeModel(GL_FLAT);
	//glShadeModel(GL_SMOOTH);   // default


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 1, 3, 0, 0, 0, 0, 1, 0);

	for (int i=0; i<6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &cubeIndices[4*i]);

	/*glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);*/

	glFlush();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -20, 20);
	else
		glOrtho(-2, 2, -2*h/w, 2*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = w;
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -20, 20);
	glMatrixMode(GL_MODELVIEW);
		
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
}


void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}