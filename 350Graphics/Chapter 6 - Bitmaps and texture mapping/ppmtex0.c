#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int n;
int m;

GLuint *image;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(0, 0);
	glDrawPixels(n, m, GL_RGB, GL_UNSIGNED_INT, image);
	glFlush();
}

void myreshape(int h, int w)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) n, 0.0, (GLfloat) m);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,h,w);
}


int main(int argc, char **argv)
{
	FILE *fd;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;
	
	fopen_s(&fd, "robot2.ppm", "r");	
	fgets(b, 100, fd);

	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n", b); 
		exit(0);
	}
	printf("%s is a PPM file\n",b);

	c = fgetc(fd);
	while(c == '#') 
	{
		fgets(b, 256, fd);
		printf("%s\n",b);

		c = fgetc(fd);
	}
	ungetc(c,fd); 

	fscanf_s(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	image = (GLuint *)malloc(3*sizeof(GLuint)*nm);

	s=255.0/k;

	if ( k == 255 )
	{
		for ( i=0; i<nm; i++ )
		{
			fscanf_s(fd,"%d %d %d",&red, &green, &blue );
			image[3*nm-3*i-3]=red;
			image[3*nm-3*i-2]=green;
			image[3*nm-3*i-1]=blue;
		}
	}else
	{
		for(i=0;i<nm;i++) 
		{
			fscanf_s(fd,"%d %d %d",&red, &green, &blue );
			image[3*nm-3*i-3]=red * s;
			image[3*nm-3*i-2]=green * s;
			image[3*nm-3*i-1]=blue * s;
		}
	}
	printf("reading image\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(n, m);
	glutInitWindowPosition(0,0);
    glutCreateWindow("Read a PPM image");
	glutReshapeFunc(myreshape);
    glutDisplayFunc(display);

	glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);	// pixel-store mode
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glClearColor(0.5, 0.5, 0.5, 1.0);

    glutMainLoop();
}


