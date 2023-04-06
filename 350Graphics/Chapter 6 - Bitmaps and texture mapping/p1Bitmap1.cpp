#include <GL/glut.h>

GLint ww = 512, wh = 512;
GLubyte check[512];

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (float)ww, 0, (float)wh);
	glMatrixMode(GL_MODELVIEW);
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
	glColor3f(0, 1, 1);
	glRasterPos2f(0, 0);       // the position of the world system


	glBitmap(64, 64, 0, 0, 100, 0, check);		// add (100, 0) to the previous raster position
	glBitmap(64, 64, 0, 0, 0, 0, check);		// start at the new raster position (100, 0)

	glBitmap(64, 64, 0, -100, 0, 0, check);		// shift up by 100 from the previous raster position (100, 0). The raster position does not change.
	glBitmap(64, 64, 100, -100, 0, 0, check);	// shift left by 100 and shift up by 100 from the previous raster position (100, 0).

	glBitmap(64, 64, 132, -200, 0, 200, check);	// shift left by 132 and up by 200 from the previous position (100, 0), and then add (0, 200) to the previous position (100, 0). The new position is (100, 200)
	glBitmap(64, 64, 0, 0, -100, 100, check);	// add (-100, 100) to the previous position (100, 200). The new position is (0, 300).

	glBitmap(32, 128, 0, 0, 32, 0, check);
	glBitmap(128, 32, 0, 0, 128, 0, check);
	glBitmap(256, 16, 0, 0, 0, 0, check);
	
	glFlush();
}

void main()
{
	GLubyte wb[2] = {0x00, 0xff}; 
	//GLubyte wb[2] = {0, 63}; // The same pattern in decimal.

	for (int i=0; i<64; i++)
		for (int j=0; j<8; j++)
			check[i*8+j] = wb[(i/8+j)%2];

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("bitmap");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}