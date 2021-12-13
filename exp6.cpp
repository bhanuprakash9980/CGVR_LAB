#include<iostream>
#include "GL/glut.h"
#include<math.h>

#define SPR 75
#define DPI (3.1415/180.f)
#define SPHERE_GA(p1,p2) {SPR*sin(DPI*(p1))*cos(DPI*(p2)),SPR*cos(DPI*(p1))*cos(DPI*(p2)),SPR*sin(DPI*(p2))}
int state = 0;
void displayLoop() {
	//glClearColor(0, 0, 0, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(1.f, 1.f, 1.f, 0.f);

	//for(int i=0;i<STEPS;i++){
	//0 - > 70
	float c0 = .1f;
	for (int i = -80; i < 80; i += 10) {

		glBegin(GL_QUAD_STRIP);
		for (int thet = -180; thet <= 180; thet += 10) {
			glColor3f(c0, c0, c0); c0 += .00125;
			float p1[3] = SPHERE_GA(thet, i);
			glVertex3fv(p1);
			float p2[3] = SPHERE_GA(thet, i + 10);
			glVertex3fv(p2);
		}
		glEnd();
	}


	//north cap
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, SPR);
	glColor3i(0.25, 0.25, 0);

	for (int thet = -180; thet <= 180; thet += 10) {
		glColor3f((thet + 180) / 360, .25, .25);
		float p1[3] = SPHERE_GA(thet, 80);
		glVertex3fv(p1);
	}
	glEnd();

	//south cap
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -SPR);
	glColor3i(0, 0.25, .25);

	for (int thet = -180; thet <= 180; thet += 10) {
		glColor3f((thet + 180) / 360, .25, .25);
		float p1[3] = SPHERE_GA(thet, -80);
		glVertex3fv(p1);
	}

	glEnd();



	glFlush();

}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -200, 200);
	glMatrixMode(GL_PROJECTION);
}


int main(int argc, char** argv) {
	std::cout << "Hello world" << std::endl;
	glutInit(&argc, argv);
	//single buffer, 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Send help");
	int w = 800, h = 600;
	glutInitWindowSize(w, h);

	glutReshapeFunc(reshape);
	glutDisplayFunc(displayLoop);

	glClearColor(0, 0, 0, 1.f);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -200, 200);
	glMatrixMode(GL_PROJECTION);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutMainLoop();

	/*glClearColor(0, 0, 0, 1.f);
	glutMainLoop();
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -200, 200);
	glMatrixMode(GL_PROJECTION);*/
}