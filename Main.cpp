#ifdef WIN32
	#define WINDOWS
#elif WIN64
	#define WINDOWS
#endif
#ifdef WINDOWS
	#include <windows.h>
#endif

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#define WIDTH 800
#define HEIGHT 800

#include <iostream>
using namespace std;
#include "Scene.h"
#include "Sphere.h"
#include "Rect.h"
#include "DataStructures.h"

VRC vrc;
CanonicalVolume canVol;
Light l;
Scene* scene;
double stepx = 0;
double stepy = 0;

Intensity average (const Intensity& c1, const Intensity& c2, const Intensity& c3, const Intensity& c4)
{
	float r = (c1.r+c2.r+c3.r+c4.r)/4;
	float g = (c1.g+c2.g+c3.g+c4.g)/4;
	float b = (c1.b+c2.b+c3.b+c4.b)/4;
	return Intensity (r, g, b);
}

void init_scene (int MAX_DEPTH)
{
	scene = new Scene (MAX_DEPTH, vrc.prp);
	scene->set_ambient (Intensity (1.0, 1.0, 1.0));
	scene->set_pls (Point (0, 40, 5), Intensity (1.0, 1.0, 1.0));

	Sphere* s1 = new Sphere (-15.0, 0, -40.0, 20.0);
	s1->material.kA.set (0.231, 0.231, 0.231);
	s1->material.kD.set (0.278, 0.278, 0.278);
	s1->material.kS.set (0.774, 0.774, 0.774);
	s1->material.kT.set (0.0, 0.0, 0.0);
	s1->material.n = 89.6;
	s1->material.kR = 0;
	scene->objects.push_back (s1);

	Sphere* s2 = new Sphere (Point (25.0, 0, -30.0), 10.0);

	s2->material.kA.set (0.231,0.231,0.231);
	s2->material.kD.set (0.278,0.278,0.278);
	s2->material.kS.set (0.774,0.774,0.774);
	s2->material.kT.set (0.0, 0.0, 0.0);
	s2->material.n = 89.6;
	s2->material.kR = 0;

	scene->objects.push_back (s2);

	//left wall
	{
		Point ps1[] = { Point(-40.0, -20.0, -10.0), Point(-40.0, 30.0, -10.0),
			Point(-40.0, 30.0, -80.0), Point(-40.0, -20.0, -80.0) };
		Rect* r1 = new Rect (ps1);
		r1->material.kA.set (0.35, 0.06, 0.02);
		r1->material.kD.set (0.82, 0.2, 0.1);
		r1->material.kS.set (0.1, 0.1, 0.1);
		r1->material.kT.set (0.0, 0.0, 0.0);
		r1->material.n = 5.0;
		r1->material.kR = 0;

		scene->objects.push_back (r1);
	}
	//right wall
	{
		Point ps2[] = { Point(40.0, -20.0, -10.0), Point(40.0, 30.0, -10.0),
			Point(40.0, 30.0, -80.0), Point(40.0, -20.0, -80.0) };
		Rect* r2 = new Rect (ps2);
		r2->material.kA.set (0.06, 0.35, 0.02);
		r2->material.kD.set (0.521,0.72,0.2);
		r2->material.kS.set (0.1, 0.1, 0.1);
		r2->material.kT.set (0.0, 0.0, 0.0);
		r2->material.n = 5.0;
		r2->material.kR = 0;
		
		scene->objects.push_back (r2);
	}
	//back wall
	{
		Point ps3[] = { Point(-40.0, -20.0, -80.0), Point(-40.0, 30.0, -80.0),
			Point(40.0, 30.0, -80.0), Point(40.0, -20.0, -80.0) };
		Rect* r3 = new Rect (ps3);
		r3->material.kA.set (0.02, 0.06, 0.35);
		r3->material.kD.set (0.1, 0.2, 0.8);
		r3->material.kS.set (0.1, 0.1, 0.1);
		r3->material.kT.set (0.0, 0.0, 0.0);
		r3->material.n = 5.0;
		r3->material.kR = 0;
		
		scene->objects.push_back (r3);
	}
	//floor
	Point ps[] = { Point(-40.0, -20.0, 80.0), Point(-40.0, -20.0, -80.0),
		Point(40.0, -20.0, -80.0), Point(40.0, -20.0, 80.0) };

	Rect* r = new Rect (ps);
	r->material.kA.set (1.0,1.0,1.0);
	r->material.kD.set (1.0,1.0,1.0);
	r->material.kS.set (1.0,1.0,1.0);
	r->material.kT.set (0.0, 0.0, 0.0);
	r->material.n = 5.0;
	scene->objects.push_back (r);
}

/* Display function */
void display () {
	/* clear the screen to the clear colour */
	glClear (GL_COLOR_BUFFER_BIT);

	glBegin (GL_POINTS);
		for (int j=0;j<HEIGHT;j++)
		{
			for (int i=0;i<WIDTH;i++)
			{
				Point p1 (canVol.uMin+stepx*i, canVol.vMin+stepy*j, vrc.vrp.z);
				Point p2 (canVol.uMin+stepx*(i+1), canVol.vMin+stepy*j, vrc.vrp.z);
				Point p3 (canVol.uMin+stepx*i, canVol.vMin+stepy*(j+1), vrc.vrp.z);
				Point p4 (canVol.uMin+stepx*(i+1), canVol.vMin+stepy*(j+1), vrc.vrp.z);
				
				Ray r1 (vrc.prp, p1-vrc.prp);
				Intensity c1 = scene->raytrace (r1, 0);

				// Ray r2 (vrc.prp, p2-vrc.prp);
				// Intensity c2 = scene->raytrace (r2, 0);

				// Ray r3 (vrc.prp, p3-vrc.prp);
				// Intensity c3 = scene->raytrace (r3, 0);

				// Ray r4 (vrc.prp, p4-vrc.prp);
				// Intensity c4 = scene->raytrace (r4, 0);

				// Intensity c = average (c1, c2, c3, c4);
				// glColor3f (c.r, c.g, c.b);
				glColor3f(c1.r, c1.g, c1.b);
				glVertex2i (i, j);
			}
		}
	glEnd ();
	// cout<<"done"<<endl;
	// delete[] scene->objects [0];
	exit (EXIT_SUCCESS);

	glFlush ();
	/* swap buffers */
	glutSwapBuffers ();
}

/**
*	For keyboard input
*/
void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:	//ESCAPE key
			exit(0);
			break;
	}
	glutPostRedisplay ();
}

void reshape (int w, int h) {
	/* set the viewport */
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	/* Matrix for projection transformation */
	glMatrixMode (GL_PROJECTION);

	/* replaces the current matrix with the identity matrix */
	glLoadIdentity ();

	/* Define a 2d orthographic projection matrix */
	gluOrtho2D (0.5, (GLdouble) w, 0.5, (GLdouble) h);
}

void idle () {}

void init (int argc, char** argv)
{
	/* deal with any GLUT command Line options */
	glutInit(&argc, argv);

	/* create an output window */
	glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (530,0);

	/* set the name of the window and try to create it */
	glutCreateWindow("CS 488 - Project 3");

	/* specify clear values for the color buffers */
	glClearColor (0.0, 0.0, 0.0, 1.0);

	/* Receive keyboard inputs */
    glutKeyboardFunc (keyboard);

	/* assign the display function */
	glutDisplayFunc(display);

	/* assign the idle function */
	// glutIdleFunc(idle);
	// glutIdleFunc(idle);

	/* sets the reshape callback for the current window */
	glutReshapeFunc(reshape);

	/* enters the GLUT event processing loop */
	glutMainLoop();
}

int main (int argc, char** argv) {
	vrc.prp = Point (0,0,10);
	vrc.vrp = Point (0,0,-10);
	vrc.vpn = Point (0,0,1);
	vrc.vup = Point (0,1,0);

	int MAX_DEPTH = 0;
	if (argc > 1)
		MAX_DEPTH = atoi (argv[1]);

	canVol.uMin = canVol.vMin = -40;
	canVol.uMax = canVol.vMax = 40;
	stepx = (canVol.uMax-canVol.uMin)/WIDTH;
	stepy = (canVol.vMax-canVol.vMin)/HEIGHT;

	init_scene (MAX_DEPTH);
	
	init (argc, argv);
	delete[] scene;
	return 0;
}