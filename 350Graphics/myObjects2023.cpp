#pragma once
#include <math.h>
#include <GL\glut.h>


const GLfloat DtoR = 0.017453;
const GLfloat Pi = 3.14159;


void axes(float length);
void circle(float x0, float y0, float r);
void cone(float r, float h);
void cylinder(float r, float h);
void parabola(float a, float b, float c, float x1, float x2);
void cube(float sideLength);
void sphere(float r, int slices, int stacks);

inline void sphere(float r, int slices, int stacks)
{
	//phi: 0-180
	//theta: 0-360
	// p1
	//x= r sin(phi) cos(theta)
	// y = r sin(phi)sin(theta)
	//z = r cos(phi)
	//p2
	//x=rsin(phi+dphi)cos(theta)
	//y=rsin(phi+dphi)sin(theta)
	//z=rcos(phi+dphi)
	//p3
	//x=rsin(phi+dphi)cos(theta+dtheta)
	//y= rsin(phi+dphi)sin(theta+dtheta)
	//z=rcos(phi+dphi_
	//p4
	//x=rsin(phi)cos(theta+dtheta)
	//y=rsin(phi)sin*theta+dtheta)
	//z=rcos(phi)
	int longitude = 360 / slices;
	int latitude = 180 / stacks;
	int phi, theta;
	float p1[3], p2[3], p3[3], p4[3];

	for (phi = 0; phi < 180; phi += latitude) {
		for (theta = 0; theta < 360; theta += longitude) {
			p1[0] = r * sin(phi * DtoR) * cos(theta * DtoR);
			p1[1] = r * sin(phi * DtoR) * sin(theta * DtoR);
			p1[2] = r * cos(phi * DtoR);

			p2[0] = r * sin((phi + latitude) * DtoR) * cos(theta * DtoR);
			p2[1] = r * sin((phi + latitude) * DtoR) * sin(theta * DtoR);
			p2[2] = r * cos((phi + latitude) * DtoR);

			p3[0] = r * sin((phi + latitude) * DtoR) * cos((theta + longitude) * DtoR);
			p3[1] = r * sin((phi + latitude) * DtoR) * sin((theta + longitude) * DtoR);
			p3[2] = r * cos((phi + latitude) * DtoR);

			p4[0] = r * sin(phi * DtoR) * cos((theta + longitude) * DtoR);
			p4[1] = r * sin(phi * DtoR) * sin((theta + longitude) * DtoR);
			p4[2] = r * cos(phi * DtoR);

			glBegin(GL_POLYGON);
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
			glEnd();

		}
	}

}
inline void cube(float sideLength) {
	float a = sideLength / 2;
	glBegin(GL_POLYGON);
	glVertex3f(a, a, a);
	glVertex3f(-a, a, a);
	glVertex3f(-a, -a, a);
	glVertex3f(a, -a, a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-a, -a, -a);
	glVertex3f(-a, a, -a);
	glVertex3f(a, a, -a);
	glVertex3f(a, -a, -a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-a, -a, -a);
	glVertex3f(-a, -a, a);
	glVertex3f(-a, a, a);
	glVertex3f(-a, a, a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(a, a, a);
	glVertex3f(a, a, -a);
	glVertex3f(-a, a, -a);
	glVertex3f(-a, a, a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(a, a, a);
	glVertex3f(a, -a, a);
	glVertex3f(a, -a, -a);
	glVertex3f(a, a, -a);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-a, -a, -a);
	glVertex3f(a, -a, -a);
	glVertex3f(a, -a, a);
	glVertex3f(-a, -a, a);
	glEnd();
}


inline void axes(float length) {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-length/2, 0, 0);
	glVertex3f(length / 2, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, -length / 2, 0);
	glVertex3f(0, length / 2, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -length / 2);
	glVertex3f(0, 0, length / 2);
	glEnd();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(length / 2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(0.1, 0.4, 10, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, length / 2, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.1,0.4,10,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, length / 2);
	glutSolidCone(0.1, 0.4, 10, 20);
	glPopMatrix();

	glPopAttrib();
	glPopMatrix();
}
inline void parabola(float a, float b, float c, float x1, float x2)
{
	float x, y;
	float dx = 0.01;

	x = x1;
	glBegin(GL_LINE_STRIP);
	while (x <= x2)
	{
		y = a * x*x + b * x + c;

		glVertex2f(x, y);

		x += dx;
	}
	glEnd();
}

inline void cylinder(float r, float h)
{
	glBegin(GL_QUAD_STRIP);
	for (int theta = 0; theta <= 360; theta += 5)
	{
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), h);
	}

	glEnd();
}

inline void cone(float r, float h)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0, h);
	for (int theta = 0; theta <= 360; theta += 5)
		glVertex3f(r*cos(theta*DtoR), r*sin(theta*DtoR), 0);

	glEnd();
}

inline void circle(float x0, float y0, float r)
{
	float theta, dTheta = 1;
	int count;
	float x, y;

	count = (int)(360.0 / dTheta);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= count; i++)
	{
		theta = i * dTheta*DtoR;
		x = x0 + r * cos(theta);
		y = y0 + r * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

