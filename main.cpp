
#include "common.h"
#include "hexagons.h"


std::auto_ptr<Hexagons> pHexagons;

GLfloat rot = 0.0f;
GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
//GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


GLfloat angle = 0.0f;
GLint hex_id = 0;
GLfloat cam_z = 0.0f;
#define NUM_TEXTURES 8

char* texture_filenames[ NUM_TEXTURES ] = {
    "shrek.png",
    "fiona.png",
    "donkey.png",
    "charming.png",
    "gingerbread.png",
    "lord.png",
    "cat.png",
    "pinocchio.png"
};

GLuint textures[ NUM_TEXTURES ];

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
/*
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight );

	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
*/
    std::vector<Hexagon*>::iterator current = pHexagons->begin();
	std::vector<Hexagon*>::iterator last = pHexagons->end();

    int cnt=0;
  //  glColor3f( 0.0f, 0.0f, 1.0f );

   glEnable( GL_TEXTURE_2D );


    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
 //   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
   //                  GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // the texture wraps over at the edges (repeat)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int tex_num = 0;

glMatrixMode(GL_MODELVIEW);

    for (;current!=last;current++) {
        glLoadIdentity();

        glBindTexture( GL_TEXTURE_2D, textures[tex_num] );
        tex_num++;
        if (tex_num>=NUM_TEXTURES) tex_num = 0;


glTranslatef( 0.0f,00.0f,-30.0f );
 glRotatef( angle, 1.0f, 0.0, 0.0f );


        glTranslatef( (*current)->x, (*current)->y, 0.0f );
        //glScalef( 5.0f, 5.0f, 5.0f );
        glRotatef( rot+(cnt), 1.0f, 0.0, 0.0f );

        glCallList(1);

        cnt+=1;
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

    //glRotatef(90.0f,1.0f,0,0);
}

/* timer event handler */
void onTimer( int id ) {
	rot+=2.0f;
	if (rot>360.0f) rot-=360.0f;

	angle+=0.50f;
	if (angle>360.0f) angle-=360.0f;
	glutPostRedisplay();
	glutTimerFunc( 10, onTimer, 1 );
}

void setup() {

    for (int i=0; i<NUM_TEXTURES; i++) {
        textures[i] = SOIL_load_OGL_texture
        (
            texture_filenames[i],
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );

    }


GLfloat tex_coords[7][2] = {
    { 0.75f, 1.0f },
    { 1.0f,  0.5f },
    { 0.75f, 0.0f },
    { 0.25f, 0.0f },
    { 0.0f,  0.5f },
    { 0.25f, 1.0f },
    { 0.75f, 1.0f }
};

	glNewList(1, GL_COMPILE );

    // setup texture mapping
      //glEnable( GL_TEXTURE_2D );
      //glBindTexture( GL_TEXTURE_2D, 1 );

		glBegin( GL_TRIANGLE_FAN );

            glTexCoord2d( 0.5f, 0.5f );
            glVertex3f( 0.0f, 0.0f, 0.0f );

		for (int p=0; p<7; p++ )
		{
			GLfloat angle = 30.0f + (p*60.0f);

			GLfloat x = 1.0f*sin(deg_to_rad(angle));
			GLfloat y = 1.0f*cos(deg_to_rad(angle));

			glTexCoord2d( tex_coords[p][0] , tex_coords[p][1] );
			glVertex3f( x, y, 0.0f );


		}


		glEnd();

	glEndList();

}

int main (int argc, char * argv[]) {

    pHexagons = std::auto_ptr<Hexagons>( Hexagons::create( 10 ) );

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
