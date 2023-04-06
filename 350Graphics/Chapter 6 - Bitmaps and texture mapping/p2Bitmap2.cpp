
#include <GL/glut.h>

GLint ww = 500, wh = 500;
GLubyte check[512];

void init()
{
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_XOR);
	//glLogicOp(GL_CLEAR);
	//glLogicOp(GL_AND);
	//glLogicOp(GL_AND_REVERSE);
	//glLogicOp(GL_COPY);
	//glLogicOp(GL_AND_INVERTED);
	//glLogicOp(GL_NOOP);
	//glLogicOp(GL_OR);
	//glLogicOp(GL_NOR);
	//glLogicOp(GL_EQUIV);
	//glLogicOp(GL_INVERT);
	//glLogicOp(GL_OR_REVERSE);
	//glLogicOp(GL_COPY_INVERTED);
	//glLogicOp(GL_OR_INVERTED);
	//glLogicOp(GL_NAND);
	//glLogicOp(GL_SET);

	glClearColor(1, 1, 0, 1);	// background color 
	//glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (float)ww, 0, (float)wh);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//glBitmap(64, 64, 0, 0, 0, 0, check);
		//glBitmap(64, 64, 0, 0, 0, 0, check);

		glColor3f(1, 0, 0);	
		glRasterPos2i(x, wh - y);

		glBitmap(64, 64, 0, 0, 0, 0, check);
		glFlush();   // force to display immediately
	}
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0, (float)w, 0, (float)h);
	
	glMatrixMode(GL_MODELVIEW);

	ww = w;
	wh = h;
	glViewport(0, 0, w, h);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);
	glRectf(200, 200, 300, 300);

	glColor3f(1, 0, 0);		// the color is locked by the followed function glRasterPos2f
 	glRasterPos2f(0, 0); 

//	glBitmap(64, 64, 0, 0, 0, 0, check);
//	glBitmap(32, 128, 0, 0, 0, 0, check);
//	glBitmap(64, 4, 0, 0, 0, 0, check);
	glBitmap(64, 64, 0, 0, 0, 0, check);

	glFlush();
}



void main()
{
	GLubyte wb[2] = {0x00, 0xff}; 

	for (int i=0; i<64; i++)
		for (int j=0; j<8; j++)
			check[i*8+j] = wb[(i/8+j)%2];

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("bitmap");
	init();

	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}