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
#include <string.h>
#include "Scene.h"
#include "Sphere.h"
#include "Floor.h"
#include "DataStructures.h"
#include "Cylinder.h"
#include "Cone.h"

VRC vrc;
CanonicalVolume canVol;
Light l;
Scene* scene;
double stepx = 0;
double stepy = 0;
bool antialiasing = false;

// average intensities from the antialiasing rays
Intensity average (const Intensity& c1, const Intensity& c2, const Intensity& c3, const Intensity& c4)
{
	float r = (c1.r+c2.r+c3.r+c4.r)/4;
	float g = (c1.g+c2.g+c3.g+c4.g)/4;
	float b = (c1.b+c2.b+c3.b+c4.b)/4;
	return Intensity (r, g, b);
}

// create objects in the scene
void init_scene (int MAX_DEPTH)
{
	scene = new Scene (MAX_DEPTH);
	scene->set_ambient (Intensity (0.5,0.5,0.5));//(1.0, 1.0, 1.0));
	scene->set_pls (Point (0, 29, 5), Intensity (0.7,0.7,0.7));

	Sphere* s1 = new Sphere (-15.0, 0, -40.0, 20.0);
	s1->material.kA.set (0.231, 0.231, 0.231);
	s1->material.kD.set (0.278, 0.278, 0.278);
	s1->material.kS.set (0.774, 0.774, 0.774);
	s1->material.kT.set (0.0, 0.0, 0.0);
	s1->material.n = 89.6;
	s1->material.kR = 0.0;

	scene->objects.push_back (s1);

	Sphere* s2 = new Sphere (Point (25.0, 0, -30.0), 10.0);

	s2->material.kA.set (0.231,0.231,0.231);
	s2->material.kD.set (0.278,0.278,0.278);
	s2->material.kS.set (0.774,0.774,0.774);
	s2->material.kT.set (0.0, 0.0, 0.0);
	s2->material.n = 89.6;
	s2->material.kR = 0.0;

	scene->objects.push_back (s2);

	Cylinder* c = new Cylinder (Point (30.0, -19.0, -14.0), 10.0,3.0);

	c->material.kA.set (0.2,0.2,0.2);
	c->material.kD.set (0.4,0.4,0.4);
	c->material.kS.set (0.4,0.4,0.4);
	c->material.kT.set (0.0, 0.0, 0.0);
	c->material.n = 89.6;
	c->material.kR = 0.0;

	scene->objects.push_back (c);

	Cone* cone = new Cone (Point (10.0, -19.0, -30.0), 10.0,3.0);

	cone->material.kA.set (0.2,0.2,0.2);
	cone->material.kD.set (0.4,0.4,0.4);
	cone->material.kS.set (0.4,0.4,0.4);
	cone->material.kT.set (0.0, 0.0, 0.0);
	cone->material.n = 89.6;
	cone->material.kR = 0.0;

	scene->objects.push_back (cone);

	//left wall
	{
		Point ps1[] = { Point(-40.0, -20.0, 80.0), Point(-40.0, 30.0, 80.0),
			Point(-40.0, 30.0, -80.0), Point(-40.0, -20.0, -80.0) };
		Rect* r1 = new Rect (ps1);
		r1->material.kA.set (0.35, 0.06, 0.02);
		r1->material.kD.set (0.82, 0.2, 0.1);
		r1->material.kS.set (0.1, 0.1, 0.1);
		r1->material.kT.set (0.0, 0.0, 0.0);
		r1->material.n = 5.0;
		r1->material.kR = 0.0;
		Vector v(1,0,0);
		r1->normal = v;

		scene->objects.push_back (r1);
	}
	//right wall
	{
		Point ps2[] = { Point(40.0, -20.0, 80.0), Point(40.0, 30.0, 80.0),
			Point(40.0, 30.0, -80.0), Point(40.0, -20.0, -80.0) };
		Rect* r2 = new Rect (ps2);
		r2->material.kA.set (0.06, 0.35, 0.02);
		r2->material.kD.set (0.521,0.72,0.2);
		r2->material.kS.set (0.1, 0.1, 0.1);
		r2->material.kT.set (0.0, 0.0, 0.0);
		r2->material.n = 5.0;
		r2->material.kR = 0.0;
		Vector v(-1,0,0);
		r2->normal = v;
		
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
		r3->material.kR = 0.0;
		Vector v(0,0,1);
		r3->normal = v;
		
		scene->objects.push_back (r3);
	}
	//front wall
	{
		Point ps4[] = { Point(-40.0, -20.0, 80.0), Point(-40.0, 30.0, 80.0),
			Point(40.0, 30.0, 80.0), Point(40.0, -20.0, 80.0) };
		Rect* r4 = new Rect (ps4);
		r4->material.kA.set (0.02, 0.35, 0.35);
		r4->material.kD.set (0.1, 0.8, 0.8);
		r4->material.kS.set (0.1, 0.1, 0.1);
		r4->material.kT.set (0.0, 0.0, 0.0);
		r4->material.n = 5.0;
		r4->material.kR = 0.0;
		Vector v(0,0,-1);
		r4->normal = v;
		
		scene->objects.push_back (r4);
	}
	{
		//floor
		Point ps[] = { Point(-40.0, -20.0, 80.0), Point(-40.0, -20.0, -80.0),
			Point(40.0, -20.0, -80.0), Point(40.0, -20.0, 80.0) };

		Floor* r = new Floor (ps,12,50);
		r->material.kA.set (0.6,0.6,0.6);//(1.0,1.0,1.0);
		r->material.kD.set (0.6,0.6,0.6);//(1.0,1.0,1.0);
		r->material.kS.set (0.6,0.6,0.6);//(1.0,1.0,1.0);
		r->material.kT.set (0.0, 0.0, 0.0);
		r->material.kR = 0.0;
		r->material.n = 5.0;

		r->material2.kA.set (0.0, 0.0, 0.0);
		r->material2.kD.set (0.0, 0.0, 0.0);
		r->material2.kS.set (0.1, 0.1, 0.1);
		r->material2.kT.set (0.0, 0.0, 0.0);
		r->material2.n = 5.0;
		r->material2.kR = 0.0;
			Vector v(0,1,0);
			r->normal = v;
		scene->objects.push_back (r);
	}

	{
		//ceiling
		Point ps[] = { Point(-40.0, 30.0, 80.0), Point(-40.0, 30.0, -80.0),
			Point(40.0, 30.0, -80.0), Point(40.0, 30.0, 80.0) };

		Floor* r = new Floor (ps,12,40);
		r->material.kA.set (1.0,1.0,1.0);
		r->material.kD.set (1.0,1.0,1.0);
		r->material.kS.set (1.0,1.0,1.0);
		r->material.kT.set (0.0, 0.0, 0.0);
		r->material.n = 5.0;
		r->material2.kA.set (0.0, 0.0, 0.0);
		r->material2.kD.set (0.0, 0.0, 0.0);
		r->material2.kS.set (0.1, 0.1, 0.1);
		r->material2.kT.set (0.0, 0.0, 0.0);
		r->material2.n = 5.0;
			Vector v(0,-1,0);
			r->normal = v;
		scene->objects.push_back (r);
	}
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
				
				double d;
				bool deb = i==650 && j==517;
				Intensity c;
				// Use antialiasing with 4 rays
				if(antialiasing)
				{
					// Pixels of the window for the 4 rays
					Point p1 (canVol.uMin+stepx*(i-0.5), canVol.vMin+stepy*(j-0.5), vrc.vrp.z);
					Point p2 (canVol.uMin+stepx*(i-0.5), canVol.vMin+stepy*(j+0.5), vrc.vrp.z);
					Point p3 (canVol.uMin+stepx*(i+0.5), canVol.vMin+stepy*(j+0.5), vrc.vrp.z);
					Point p4 (canVol.uMin+stepx*(i+0.5), canVol.vMin+stepy*(j-0.5), vrc.vrp.z);

					Ray r1 (vrc.prp, p1-vrc.prp, 1.0, deb);
					c = scene->raytrace (r1, 0);

					Ray r2 (vrc.prp, p2-vrc.prp, 1.0);
					Intensity c2 = scene->raytrace (r2, 0);

					Ray r3 (vrc.prp, p3-vrc.prp, 1.0);
					Intensity c3 = scene->raytrace (r3, 0);

					Ray r4 (vrc.prp, p4-vrc.prp, 1.0);
					Intensity c4 = scene->raytrace (r4, 0);

					// average the 4 intensities
					c = average (c, c2, c3, c4);
				} else 
				{
					// no antialiasing
					Point p (canVol.uMin+stepx*(i), canVol.vMin+stepy*(j), vrc.vrp.z);
					Ray r (vrc.prp, p-vrc.prp, 1.0, deb);

					c = scene->raytrace (r, 0);
				}

				glColor3f (c.r, c.g, c.b);
				glVertex2f (i, j);
			}
		}
	glEnd ();
	cout<<"done"<<endl;

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

	/* sets the reshape callback for the current window */
	glutReshapeFunc(reshape);
	/* enters the GLUT event processing loop */
	glutMainLoop();
}

int main (int argc, char** argv) {
	vrc.prp = Point (0,0,80);
	vrc.vrp = Point (0,0,-10);
	vrc.vpn = Point (0,0,1);
	vrc.vup = Point (0,1,0);

	int MAX_DEPTH = 0;
	if (argc > 1)
	{
		//maximum depth argument
		MAX_DEPTH = atoi (argv[1]);

		// antialiasing argument
		if(argc>2)
			antialiasing = strcmp (argv[2], "-aa") == 0;
	}

	canVol.uMin = canVol.vMin = -40;
	canVol.uMax = canVol.vMax = 40;
	stepx = (canVol.uMax-canVol.uMin)/WIDTH;
	stepy = (canVol.vMax-canVol.vMin)/HEIGHT;

	init_scene (MAX_DEPTH);
	
	init (argc, argv);
	delete[] scene;
	return 0;
}