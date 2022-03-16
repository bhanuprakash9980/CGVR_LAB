#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

void sphere()
{
	double c = 3.142 / 180, phi, phir, phir20, theta, thetar, x, y, z, c80; // converting to radians
	// to get longitudes
	for (phi = -80.0; phi <= 60.0; phi += 20.0)
	{
		//phi=-50.0;
		phir = c * phi;  //  in radians – for the 1st point
		phir20 = c * (phi + 20);  // for the 2nd point
		glBegin(GL_QUAD_STRIP);
		// to get latitudes
		for (theta = -180.0; theta <= 180.0; theta += 20.0)
		{
			thetar = c * theta;  // =-180*c = -3.132 – 1st time

			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x, y, z); // 1st point

			phir20 = c * (phi + 20);
			x = sin(thetar) * cos(phir20);
			y = cos(thetar) * cos(phir20);
			z = sin(phir20);
			glVertex3d(x, y, z); // 2nd point



		}
		glEnd();
	}

	//1st pole – use triangle fans
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, 1.0);   // top pole
	c80 = c * 80.0;
	z = sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();
	//2nd pole – use triangle fans
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, -1.0); // bottom pole
	z = -sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 20.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -1);
	glRotatef(-90.0, 0.0, 1.0, 0.0);

	sphere();

	glFlush();
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(0, 0, 1.0);
	glPointSize(1.0);
	gluOrtho2D(-1, 1, -1, 1);
}
void main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Display");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
