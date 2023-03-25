#include "../myObjects2023.cpp"

GLsizei ww = 512, wh = 512;
GLfloat angles[3] = {0, 0, 0};
GLfloat increment = 5; 
GLfloat halfWidth = 4;
GLfloat halfHeight = 4;

void display1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	glLineWidth(2);
	axes(4); // the reference for all

	// The combination of the three rotations make the overall transformation start from the current position.
	glRotatef(angles[0], 1, 0, 0);
	glRotatef(angles[1], 0, 1, 0);
	glRotatef(angles[2], 0, 0, 1);
	
	//-------------the object with a reference axis
	glLineWidth(1);
	axes(2);

	glColor3f(0, 1, 1);
	glutWireCube(1);
	//-------------------------------------------

	glutPostRedisplay();
	glutSwapBuffers();
}

void display2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	axes(6);	// axis for the entire space

	//The combination of the three rotations make the overall transformation start from the current position.
	//glRotatef(angles[0], 1, 0, 0);
	//glRotatef(angles[1], 0, 1, 0);
	glRotatef(angles[2], 0, 0, 1);

	//------ translate to the side before rotation --------
	axes(4); // for reference
	glTranslatef(2, 0, 0);
	//----------------------------------------------------

	//-------------the object with a reference axis
	axes(2);

	glColor3f(0, 0, 0);
	glutWireCube(1);
	//-------------------------------------------

	glutPostRedisplay();
	glutSwapBuffers();
}

void display3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);

	axes(6);	// axis for the entire space

	// The combination of the three rotations make the overall transformation start from the current position.
	//glRotatef(angles[0], 1, 0, 0);
	//glRotatef(angles[1], 0, 1, 0);
	glRotatef(angles[2], 0, 0, 1);

	axes(4);	// for reference
	glTranslatef(2, 0, 0);

	//------------cancel the effect of the above (later) rotation
	//axes(2);	// for reference
	glRotatef(-1.0*angles[2], 0, 0, 1);	
	//-------------------------------------------------

	//-------------the object with a reference axis
	axes(2);

	glColor3f(0, 0, 0);
	glutWireCube(1);
	//-------------------------------------------

	glutPostRedisplay();
	glutSwapBuffers();
}

void keys(unsigned char k, int x, int y)
{
	if (k == '1')
		glutDisplayFunc(display1);

	if (k == '2')
		glutDisplayFunc(display2);

	if (k == '3')
		glutDisplayFunc(display3);

	if (k == 'p' || k == 'P')
		if (increment < 0)
			increment = -1.0 * increment;
		else if (k == 'n' || k == 'N')
			if (increment > 0)
				increment = -1.0 * increment;

	glutPostRedisplay();
}


void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-halfWidth*w/h, halfWidth*w/h, -halfHeight, halfHeight, -20, 20);
	else
		glOrtho(-halfWidth, halfWidth, -halfHeight*h/w, halfHeight*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		angles[0] += increment;
	}

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		angles[1] += increment;
	}

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		angles[2] += increment;
	}

}

//--- only for temorary use
void tempIdle(void)
{
	angles[2] += 0.01;
	if (angles[2] >= 360)
		angles[2] -= 360;
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("translate cube");

	glutDisplayFunc(display1);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
//	glutIdleFunc(tempIdle);

	init();
	glutMainLoop();
}

