
#include "common.h"
#include "hexagons.h"


std::auto_ptr<Hexagons> pHexagons;

GLfloat rot = 0.0f;
GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
//GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };



GLint hex_id = 0;

Hexagons hexagons;

/* opengl drawing event handler */
void onRender(void) {

	/* set clear colour to black */
    glClearColor(0.0, 0.0, 0.0, 1.0);

	/* clear the buffer (to black) */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable( GL_DEPTH_TEST );
	glFrontFace( GL_CW );
	//glEnable( GL_CULL_FACE );

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight );

	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

    std::vector<Hexagon*>::iterator current = pHexagons->begin();
	std::vector<Hexagon*>::iterator last = pHexagons->end();

int cnt=0;

    for (;current!=last;current++) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef( (*current)->x, (*current)->y, -20.0f );
        //glScalef( 5.0f, 5.0f, 5.0f );
        glRotatef( rot+(cnt), 1.0f, 0.0, 0.0 );
        glColor3f( 1.0f, 0.0f, 0.0f );
        glCallList(1);

        cnt+=2;
    }

    // swap buffers
    glutSwapBuffers();
}

/* opengl window resize event handler */
void onResize(int w, int h) {

	// Prevent a divide by zero */
	if(h == 0) h = 1;

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	GLfloat aspectRatio = (GLfloat)w/ (GLfloat)h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, aspectRatio, 10.0f, 200.0f );

}

/* timer event handler */
void onTimer( int id ) {
	rot+=1.0f;
	if (rot>360.0f) rot-=360.0f;
	glutPostRedisplay();
	glutTimerFunc( 10, onTimer, 1 );
}

void setup() {
	glNewList(1, GL_COMPILE );

		glBegin( GL_TRIANGLE_FAN );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		for (int p=0; p<7; p++ )
		{
			GLfloat angle = 30.0f + (p*60.0f);

			GLfloat x = 1.0f*sin(deg_to_rad(angle));
			GLfloat y = 1.0f*cos(deg_to_rad(angle));

			glVertex3f( x, y, 0.0f );
		}
		glEnd();

	glEndList();
}

int main (int argc, char * argv[]) {

    pHexagons = std::auto_ptr<Hexagons>( Hexagons::create( 5 ) );

	/* Initialise glut with any passed command line options */
	glutInit(&argc, argv);

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH );

	/* Create a window to display the opengl output */
	glutCreateWindow( "GLUT 02" );

	/* Define the function that will be called when the opengl stuff needs to be drawn */
	glutDisplayFunc( onRender );

	/* Define the function that will be called when the window is resized */
    glutReshapeFunc( onResize );

	/* register a timer function to increment the rotations */
	glutTimerFunc( 10, onTimer, 1 );

	/* init some stuff */
	setup();

	/* Start GLUT processing */
	glutMainLoop();

    return 0;
}
