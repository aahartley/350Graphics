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
inline void normal(float p0[], float p1[], float p2[], float n[])
{
	float a[3], b[3];
	float d;

	for (int i = 0; i < 3; i++)
	{
		a[i] = p1[i] - p0[i];
		b[i] = p2[i] - p0[i];
	}

	n[0] = a[1] * b[2] - a[2] * b[1];
	n[1] = a[2] * b[0] - a[0] * b[2];
	n[2] = a[0] * b[1] - a[1] * b[0];

	d = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

	if (d == 0)
		d = 1;

	for (int i = 0; i < 3; i++)
		n[i] = n[i] / d;
}
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
	float p1[3], p2[3], p3[3], p4[3], norm[3];

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

			normal(p1, p2, p3, norm);
			glNormal3fv(norm);
			glBegin(GL_POLYGON);
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
			glEnd();

		}
	}

}
inline void head(float r, int slices, int stacks)
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
	float p1[3], p2[3], p3[3], p4[3], norm[3];

	for (phi = 0; phi < 180; phi += latitude) {
		if (phi<20 || phi>24) {
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

				normal(p1, p2, p3, norm);
				glNormal3fv(norm);
				glBegin(GL_POLYGON);
				glVertex3fv(p1);
				glVertex3fv(p2);
				glVertex3fv(p3);
				glVertex3fv(p4);
				glEnd();

			}
		}
		
	}

}
inline void cube(float sideLength) {
	float a = sideLength / 2;
	glNormal3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(a, a, a);
	glVertex3f(-a, a, a);
	glVertex3f(-a, -a, a);
	glVertex3f(a, -a, a);
	glEnd();

	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	glVertex3f(-a, -a, -a);
	glVertex3f(-a, a, -a);
	glVertex3f(a, a, -a);
	glVertex3f(a, -a, -a);
	glEnd();

	glNormal3f(-1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-a, -a, -a);
	glVertex3f(-a, -a, a);
	glVertex3f(-a, a, a);
	glVertex3f(-a, a, a);
	glEnd();

	glNormal3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(a, a, a);
	glVertex3f(a, a, -a);
	glVertex3f(-a, a, -a);
	glVertex3f(-a, a, a);
	glEnd();

	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(a, a, a);
	glVertex3f(a, -a, a);
	glVertex3f(a, -a, -a);
	glVertex3f(a, a, -a);
	glEnd();

	glNormal3f(0, -1, 0);
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
inline void drawPyramid()
{
	float p1[3], p2[3], p3[3], norm[3];

	glBegin(GL_TRIANGLES);
	//Square Base
	p1[0] = -0.25;
	p1[1] = -0.25;
	p1[2] = 0.25;
	p2[0] = 0.25;
	p2[1] = -0.25;
	p2[2] = 0.25;
	p3[0] = 0.25;
	p3[1] = -0.25;
	p3[2] = -0.25;
	normal(p3, p2, p1, norm);
	glNormal3fv(norm);
	glVertex3f(-0.25f, -0.25f, 0.25f);
	glVertex3f(0.25f, -0.25f, 0.25f);
	glVertex3f(0.25f, -0.25f, -0.25f);

	p1[0] = -0.25;
	p1[1] = -0.25;
	p1[2] = -0.25;
	p2[0] = 0.25;
	p2[1] = -0.25;
	p2[2] = -0.25;
	p3[0] = -0.25;
	p3[1] = -0.25;
	p3[2] = 0.25;
	normal(p1, p2, p3, norm);
	glNormal3fv(norm);
	glVertex3f(-0.25f, -0.25f, -0.25f);
	glVertex3f(0.25f, -0.25f, -0.25f);
	glVertex3f(-0.25f, -0.25f, 0.25f);

	p1[0] = -0.25;
	p1[1] = -0.25;
	p1[2] = 0.25;
	p2[0] = 0.25;
	p2[1] = -0.25;
	p2[2] = 0.25;
	p3[0] = 0;
	p3[1] = 0.25;
	p3[2] = 0;
	normal(p1, p2, p3, norm);
	glNormal3fv(norm);
	// Triangle Side 1
	glVertex3f(-0.25f, -0.25f, 0.25f);
	glVertex3f(0.25f, -0.25f, 0.25f);
	glVertex3f(0.0f, 0.25f, 0.0f);

	p1[0] = -0.25;
	p1[1] = -0.25;
	p1[2] = -0.25;
	p2[0] = 0.25;
	p2[1] = -0.25;
	p2[2] = -0.25;
	p3[0] = 0;
	p3[1] = 0.25;
	p3[2] = 0;
	normal(p3, p2, p1, norm);
	glNormal3fv(norm);
	// Triangle Side 2
	glVertex3f(-0.25f, -0.25f, -0.25f);
	glVertex3f(0.25f, -0.25f, -0.25f);
	glVertex3f(0.0f, 0.25f, 0.0f);
	p1[0] = -0.25;
	p1[1] = -0.25;
	p1[2] = -0.25;
	p2[0] = -0.25;
	p2[1] = -0.25;
	p2[2] = 0.25;
	p3[0] = 0;
	p3[1] = 0.25;
	p3[2] = 0;
	normal(p3, p2, p1, norm);
	glNormal3fv(norm);
	// Triangle Side 3
	glVertex3f(-0.25f, -0.25f, -0.25f);
	glVertex3f(-0.25f, -0.25f, 0.25f);
	glVertex3f(0.0f, 0.25f, 0.0f);
	p1[0] = 0.25;
	p1[1] = -0.25;
	p1[2] = -0.25;
	p2[0] = 0.25;
	p2[1] = -0.25;
	p2[2] = 0.25;
	p3[0] = 0;
	p3[1] = 0.25;
	p3[2] = 0;
	normal(p3, p2, p1, norm);
	glNormal3fv(norm);
	// Triangle Side 4
	glVertex3f(0.25f, -0.25f, -0.25f);
	glVertex3f(0.25f, -0.25f, 0.25f);
	glVertex3f(0.0f, 0.25f, 0.0f);

	glEnd();
}
inline void normalize(GLfloat* a) {
	GLfloat d = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] /= d; a[1] /= d; a[2] /= d;
}
inline void drawCircle(float xRadius, float zRadius, float yHeight)
{
	float DEF_D = 1.0f;
	float k = 0.0f;
	float p1[3], p2[3], p3[3], norm[3];

	glBegin(GL_TRIANGLES);
	for (k = 0; k <= 360; k += DEF_D) {
		p1[0] = 0;
		p1[1] = yHeight;
		p1[2] = 0;
		p2[0] = cos(k) * xRadius;
		p2[1] = yHeight;
		p2[2] = sin(k) * zRadius;
		p3[0] = cos(k + DEF_D * 0.1) * xRadius;
		p3[1] = yHeight;
		p3[2] = sin(k + DEF_D * 0.1) * zRadius;
		normal(p3, p2, p1, norm);
		glNormal3fv(norm);
		glVertex3f(0, yHeight, 0);
		glVertex3f(cos(k) * xRadius, yHeight, sin(k) * zRadius);
		glVertex3f(cos(k + DEF_D * 0.1) * xRadius, yHeight, sin(k + DEF_D * 0.1) * zRadius);
	}
	glEnd();
}
inline void drawCylinder(float x1Radius, float z1Radius, float x2Radius, float z2Radius, float height)
{
	float DEF_D = 1.0f;
	float k = 0.0f;
	float p1[3], p2[3], p3[3], norm[3];

	glBegin(GL_TRIANGLES);
	for (k = 0; k <= 360; k += DEF_D) {
		p1[0] = cos(k) * x2Radius;
		p1[1] = height;
		p1[2] = sin(k) * z2Radius;
		p2[0] = cos(k) * x1Radius;
		p2[1] = 0;
		p2[2] = sin(k) * z1Radius;
		p3[0] = cos(k + DEF_D * 0.1) * x1Radius;
		p3[1] = 0;
		p3[2] = sin(k + DEF_D * 0.1) * z1Radius;
		normal(p3, p2, p1, norm);
		glNormal3fv(norm);
		glVertex3f(cos(k) * x2Radius, height, sin(k) * z2Radius);
		glVertex3f(cos(k) * x1Radius, 0, sin(k) * z1Radius);
		glVertex3f(cos(k + DEF_D * 0.1) * x1Radius, 0, sin(k + DEF_D * 0.1) * z1Radius);

		p1[0] = cos(k) * x1Radius;
		p1[1] = 0;
		p1[2] = sin(k) * z1Radius;
		p2[0] = cos(k) * x2Radius;
		p2[1] = height;
		p2[2] = sin(k) * z2Radius;
		p3[0] = cos(k + DEF_D * 0.1) * x2Radius;
		p3[1] = height;
		p3[2] = sin(k + DEF_D * 0.1) * z2Radius;
		normal(p1, p2, p3, norm);
		glNormal3fv(norm);
		glVertex3f(cos(k) * x1Radius, 0, sin(k) * z1Radius);
		glVertex3f(cos(k) * x2Radius, height, sin(k) * z2Radius);
		glVertex3f(cos(k + DEF_D * 0.1) * x2Radius, height, sin(k + DEF_D * 0.1) * z2Radius);
	}
	glEnd();

	drawCircle(x1Radius, z1Radius, 0);
	drawCircle(x2Radius, z2Radius, height);
}

inline void drawSphereWithNormalSmooth(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	for (phi = -90; phi <= 90 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta * DtoR) * cos(phi * DtoR);
			p1[1] = radius * sin(theta * DtoR) * cos(phi * DtoR);
			p1[2] = radius * sin(phi * DtoR);

			p2[0] = radius * cos((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[1] = radius * sin((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[2] = radius * sin(phi * DtoR);

			p3[0] = radius * cos((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[1] = radius * sin((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[2] = radius * sin((phi + latitude) * DtoR);

			p4[0] = radius * cos(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[1] = radius * sin(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[2] = radius * sin((phi + latitude) * DtoR);

			glBegin(GL_POLYGON);
			glNormal3f(p1[0] / radius, p1[1] / radius, p1[2] / radius); // could be set up for every vertex
			glVertex3fv(p1);
			glNormal3f(p2[0] / radius, p2[1] / radius, p2[2] / radius);
			glVertex3fv(p2);
			glNormal3f(p3[0] / radius, p3[1] / radius, p3[2] / radius);
			glVertex3fv(p3);
			glNormal3f(p4[0] / radius, p4[1] / radius, p4[2] / radius);
			glVertex3fv(p4);
			glEnd();
		}
	}
}
inline void drawHalfSphereWithNormalSmooth(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	for (phi = -90; phi <= 0 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta * DtoR) * cos(phi * DtoR);
			p1[1] = radius * sin(theta * DtoR) * cos(phi * DtoR);
			p1[2] = radius * sin(phi * DtoR);

			p2[0] = radius * cos((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[1] = radius * sin((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[2] = radius * sin(phi * DtoR);

			p3[0] = radius * cos((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[1] = radius * sin((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[2] = radius * sin((phi + latitude) * DtoR);

			p4[0] = radius * cos(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[1] = radius * sin(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[2] = radius * sin((phi + latitude) * DtoR);

			glBegin(GL_POLYGON);
			glNormal3f(p1[0] / radius, p1[1] / radius, p1[2] / radius); // could be set up for every vertex
			glVertex3fv(p1);
			glNormal3f(p2[0] / radius, p2[1] / radius, p2[2] / radius);
			glVertex3fv(p2);
			glNormal3f(p3[0] / radius, p3[1] / radius, p3[2] / radius);
			glVertex3fv(p3);
			glNormal3f(p4[0] / radius, p4[1] / radius, p4[2] / radius);
			glVertex3fv(p4);
			glEnd();
		}
	}
}
inline void drawHalfHalfSphereWithNormalSmooth(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	for (phi = -90; phi <= -60 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta * DtoR) * cos(phi * DtoR);
			p1[1] = radius * sin(theta * DtoR) * cos(phi * DtoR);
			p1[2] = radius * sin(phi * DtoR);

			p2[0] = radius * cos((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[1] = radius * sin((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[2] = radius * sin(phi * DtoR);

			p3[0] = radius * cos((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[1] = radius * sin((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[2] = radius * sin((phi + latitude) * DtoR);

			p4[0] = radius * cos(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[1] = radius * sin(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[2] = radius * sin((phi + latitude) * DtoR);

			glBegin(GL_POLYGON);
			glNormal3f(p1[0] / radius, p1[1] / radius, p1[2] / radius); // could be set up for every vertex
			glVertex3fv(p1);
			glNormal3f(p2[0] / radius, p2[1] / radius, p2[2] / radius);
			glVertex3fv(p2);
			glNormal3f(p3[0] / radius, p3[1] / radius, p3[2] / radius);
			glVertex3fv(p3);
			glNormal3f(p4[0] / radius, p4[1] / radius, p4[2] / radius);
			glVertex3fv(p4);
			glEnd();
		}
	}
}