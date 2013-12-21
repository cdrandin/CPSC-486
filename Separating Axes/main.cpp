#include <iostream>

#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>
#endif

#include <cstdlib>
#include <ctime>

#include "Square.h"
#include "GameObject.h"
#include "Ray3.h"

// Simple constants
int SCREEN_WIDTH  = 500,
	SCREEN_HEIGHT = 500;

int ortho_size_x = 10,
	ortho_size_y = 10;

bool gPerspMode = false;

GLfloat z_pos = -0.5f;

// Velocity stuff
const double SPEED_INCR = 1.1;
double SPEED = 0.02;
Vector3 ORIGIN(  0.0,  0.0, z_pos),
		LEFT  (-SPEED,  0.0, z_pos), 
		RIGHT ( SPEED,  0.0, z_pos),
		UP    (  0.0, SPEED, z_pos),
		DOWN  (  0.0,-SPEED, z_pos);

std::vector<Vector3> random_velocity;
// End velocity stuff

// Colors
const Vector3 RED(1.0,0.0,0.0),
		GREEN(0.0,1.0,0.0),
		BLUE(0.0,0.0,1.0),
		YELLOW(RED+GREEN),
		CYAN(GREEN+BLUE),
		PURPLE(RED+BLUE),
		WHITE(RED+GREEN+BLUE),
		BLACK;

std::vector<Vector3> random_colors;
// End colors

// Turn on debug visuals
bool debug = false;

// End constants

// Start callback functions
void idle();
void reshape(int w, int h);
void display();
void keyboard( unsigned char key, int x, int y );
// End callback functions

void runGameLoop(int argc, char *argv[]);

void initScene();
void initGLUT(int , char**);
void initGL();
void end();

void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void toOrtho();
void toPerspective();

// Start collision stuff
int whichSide(const cpsc486::Square& s, const cpsc486::Ray3& r);
bool testIntersection2D(const cpsc486::Square& a, const cpsc486::Square& b);
void screenCollision();
void boxCollision();
// End collision stuff

// Helper to create square
void createSquare(const cpsc486::Square& square, const Vector3& velocity, const Vector3& color);
void makeRandomSquare();
void draw();

// Objects
std::vector<cpsc486::GameObject*> objects;


template <typename T>
void remove(std::vector<T>& vec, size_t pos)
{
    std::vector<T>::iterator it = vec.begin();
    std::advance(it, pos);
    vec.erase(it);
}

int main(int argc, char *argv[])
{
	initScene();

	createSquare(cpsc486::Square(ORIGIN, Vector3(1.0,1.0,z_pos), Vector3(-4.0,0.0,z_pos)), 
				 RIGHT, 
				 RED);

	createSquare(cpsc486::Square(ORIGIN, Vector3(1.0,1.0,z_pos), Vector3(4.0,0.0,z_pos)), 
				 LEFT,
				 BLUE);

	createSquare(cpsc486::Square(ORIGIN, Vector3(1.0,1.0,z_pos), Vector3(-4.0,4.0,z_pos)), 
				 UP+RIGHT,
				 CYAN);

	createSquare(cpsc486::Square(ORIGIN, Vector3(1.0,1.0,z_pos), Vector3(-4.0,-4.0,z_pos)), 
				 DOWN+LEFT,
				 GREEN);

	runGameLoop(argc, argv);
}

void runGameLoop(int argc, char *argv[])
{
	initGLUT(argc, argv);
	initGL();

	glutMainLoop(); 
}

void initScene()
{
	srand(time(NULL));

	random_colors.push_back(RED);
	random_colors.push_back(GREEN);
	random_colors.push_back(BLUE);
	random_colors.push_back(PURPLE);
	random_colors.push_back(CYAN);
	random_colors.push_back(YELLOW);
	random_colors.push_back(WHITE);

	random_velocity.push_back(UP);
	random_velocity.push_back(DOWN);
	random_velocity.push_back(LEFT);
	random_velocity.push_back(RIGHT);
}

void initGLUT(int argc, char** argv)
{
	// GLUT stuff for windowing
	// initialization OpenGL window.
	// it is called before any other GLUT routine
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA |GLUT_DEPTH);   // display mode

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);  // window size
	glutInitWindowPosition(1000, 100);                 // window location
	glutCreateWindow("Assignment 2");                       // window name
	
	#ifdef WIN32
		glewInit( );
	#endif

	// register GLUT callback functions
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
}

void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0f);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);
}

///////////////////////////////////////////////////////////////////////////////
// display callback function
///////////////////////////////////////////////////////////////////////////////
void display()
{
	// clear buffer
	//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	setCamera( 0.0f, 0.0f, -z_pos,  // camera position
			   0.0f, 0.0f, 0.0f ); // where to look at

	draw();

	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
// keyboard input callback function
///////////////////////////////////////////////////////////////////////////////
void keyboard( unsigned char key, int x, int y )
{
	switch( key )
	{
	case 27:
	case 'q':
		end();
		break;
	case ' ':
		makeRandomSquare();
		break;
	case '+':
	case '=':
		SPEED += SPEED_INCR;
		objects[0]->setVelocity(objects[0]->getVelocity() * SPEED_INCR);
		break;
	case '-':
		SPEED -= SPEED_INCR;
		objects[0]->setVelocity(objects[0]->getVelocity() / SPEED_INCR);
		break;
	case 8: // backspace
		remove(objects,rand()%(objects.size()-1)+1);
		break;
		/*
	case 'p':
		gPerspMode = !gPerspMode;
		reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ));
		break;
		*/
	}

	glutPostRedisplay( );
}

///////////////////////////////////////////////////////////////////////////////
// idle callback function
// Handling collision
///////////////////////////////////////////////////////////////////////////////
void idle()
{
	boxCollision();
	screenCollision();
	
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;

	if (SCREEN_HEIGHT == 0)
		SCREEN_HEIGHT = 1;

	glViewport( 0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT );

	double ratio = double(SCREEN_WIDTH) / double(SCREEN_HEIGHT);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	if( gPerspMode )
		toPerspective();
	//glFrustum(-1, 1, -1, 1, 1, 2);
	else
		toOrtho();
}

///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX   ,    posY,    posZ,  // eye(x,y,z)
			  targetX, targetY, targetZ,  // gaze(x,y,z)
					0,       1,       0); // up(x,y,z)
}

///////////////////////////////////////////////////////////////////////////////
// set projection matrix as orthogonal
///////////////////////////////////////////////////////////////////////////////
void toOrtho()
{
	// set viewport to be the entire window
	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);

	// set orthographic viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 10.0f);
	glOrtho(-ortho_size_x, ortho_size_x, -ortho_size_y, ortho_size_y, 1.0, 1.5);

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void toPerspective()
{
	// set viewport to be the entire window
	glViewport(0, 0, (GLsizei)SCREEN_WIDTH, (GLsizei)SCREEN_HEIGHT);

	// set perspective viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	                // FOV,             AspectRatio,         NearClip, FarClip
	gluPerspective(60.0f, (float)(SCREEN_WIDTH)/SCREEN_HEIGHT, 1.0f, 50.0f);

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void end()
{
	#ifdef FREEGLUT
		glutLeaveMainLoop( );
	#else
		exit( 0 );
	#endif
}

int whichSide(const cpsc486::Square& s, const cpsc486::Ray3& r)
{
	int pos = 0, neg = 0;
	cpsc486::Square square = s;
	cpsc486::Ray3 ray = r;

	Vector3 *vertex;

	for(int i=0;i<4;++i)
	{
		vertex = square.getPolygon().getVertices().at(i);

		GLfloat t = (ray.getDirection()).DotProduct(*vertex - ray.getOrigin());

		if(t>0)
			++pos;
		else if(t<0)
			--neg;
		if(pos && neg)
			return 0;
	}
	
	return (pos?1:-1);
}

bool testIntersection2D(const cpsc486::Square& a, const cpsc486::Square& b)
{
	cpsc486::Square s1(a), s2(b);

	for(int i=0;i<4;++i)
	{
		if(whichSide(s2, *(s1.getEdgeNormals()[i])) > 0)
		{
			return false;
		}
	}

	for(int i=0;i<4;++i)
	{
		if(whichSide(s1, *(s2.getEdgeNormals()[i])) > 0)
		{
			return false;
		}
	}

	return true;
}

void boxCollision()
{
	for(int i=0;i<(int)objects.size();++i)
	{
		for(int j=i+1;j<(int)objects.size();++j)
		{
			// Don't check collision with self
			if(i!=j)
			{
				if(testIntersection2D(objects.at(i)->getSquare(), objects.at(j)->getSquare()))
				{
					objects.at(i)->setVelocity(-objects.at(i)->getVelocity());
					objects.at(i)->setColor(random_colors.at(rand()%(random_colors.size()-1)+1));
					objects.at(j)->setVelocity(-objects.at(j)->getVelocity());
					objects.at(j)->setColor(random_colors.at(rand()%(random_colors.size()-1)+1));

					//Beep(500, 50);
				}
			}
		}
	}
}

void screenCollision()
{
	for(std::vector<cpsc486::GameObject*>::iterator it = objects.begin();it != objects.end();++it)
	{
		// Bounce from RIGHT side of the screen
		if ( (*it)->getSquare().getVertices()[3]->x() >= ortho_size_x )
		{
			(*it)->setVelocity(Vector3((*it)->getVelocity().x()*-1, (*it)->getVelocity().y(), (*it)->getVelocity().z()));
		}

		// Bounce from LEFT side of the screen
		else if ( (*it)->getSquare().getVertices()[1]->x() <= -ortho_size_x )
		{
			(*it)->setVelocity(Vector3((*it)->getVelocity().x()*-1, (*it)->getVelocity().y(), (*it)->getVelocity().z()));
		}

		// Bounce from TOP side of the screen
		if ( (*it)->getSquare().getVertices()[3]->y() >= ortho_size_y )
		{
			(*it)->setVelocity(Vector3((*it)->getVelocity().x(), (*it)->getVelocity().y()*-1, (*it)->getVelocity().z()));
		}

		// Bounce from BOTTOM side of the screen
		else if ( (*it)->getSquare().getVertices()[1]->y() <= -ortho_size_y )
		{
			(*it)->setVelocity(Vector3((*it)->getVelocity().x(), (*it)->getVelocity().y()*-1, (*it)->getVelocity().z()));
		}
	}
}

// A method of creating a square easily
void createSquare(const cpsc486::Square& square, const Vector3& velocity, const Vector3& color)
{
	objects.push_back(new cpsc486::GameObject());
	__int8 index = objects.size() - 1;
	objects[index]->setSquare(square);
	objects[index]->setVelocity(velocity);
	objects[index]->setColor(color);
}

// User presses button to make a square
void makeRandomSquare()
{
	bool ready = false;

	cpsc486::Square *r_square;
	Vector3 *velocity;	
	Vector3 *color;

	// Keep making a square till it is no colliding with an object already on the screen
	while(!ready)
	{
		//r_square = new cpsc486::Square(Vector3(0.0,0.0,z_pos), Vector3(rand()%ortho_size_x,rand()%ortho_size_y,z_pos),
		//												Vector3(rand()%((2*ortho_size_x)-1)+1, rand()%((2*ortho_size_x)-1)+1, rand()%((2*ortho_size_x)-1)+1));
	
		r_square = new cpsc486::Square(ORIGIN, Vector3(1.0,1.0,z_pos), Vector3((ortho_size_x/2.0) - rand()%(ortho_size_x-1)+1, (ortho_size_y/2.0) - rand()%(ortho_size_y-1)+1,z_pos));

		velocity = new Vector3(random_velocity.at(rand()%(random_velocity.size()-1)+1) + random_velocity.at(rand()%(random_velocity.size()-1)+1));	
		color = new Vector3(random_colors.at(rand()%(random_colors.size()-1)+1));

		for(int i=0;i<(int)objects.size();++i)
		{
			if(!testIntersection2D(*r_square, objects.at(i)->getSquare()))
			{
				ready = true;
				break;
			}
		}
		// Don't delete if square is ready to go for rendering
		if(!ready)
		{
			delete r_square;
			delete velocity;
			delete color;
		}
	}
	
	// Push object into render list, then delete
	createSquare(*r_square, *velocity, *color);
	delete r_square;
	delete velocity;
	delete color;
}

void draw()
{
	// Draw and move the vertices of the objects
	for(std::vector<cpsc486::GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		// Get square and call it's polygon method to draw object at position
		(*it)->getSquare().getPolygon().drawImmediate((*it)->getColor());

		// ** DEBUG **
		if(debug)
		{
			(*it)->getSquare().debugEdge();
			(*it)->getSquare().debugEdgeNormals();
			//(*it)->drawPosition();
		}
		// ***********

		// Add set velcoity to the position
		(*it)->move();
	}
}