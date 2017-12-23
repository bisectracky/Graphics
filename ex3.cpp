/*
 For VC++ users, create a Win32 Console project and link 
 the program with glut32.lib, glu32.lib, opengl32.lib
*/

#include <windows.h>   // Standard Header For MSWindows Applications
#include <gl/glut.h>   // The GL Utility Toolkit (GLUT) Header
#include "tgaload.h"

// The Following Directive Fixes The Problem With Extra Console Window
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

GLuint texture_id[3];
GLUquadricObj* g_quadratic1;
GLUquadricObj* g_quadratic2;
GLUquadricObj* g_quadratic3;
float angle = 0.0f;

// Global Variables

// Our GL Specific Initializations
bool init(void)
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glGenTextures(3, texture_id);

	g_quadratic1 = gluNewQuadric();//sun
	gluQuadricNormals(g_quadratic1, GLU_SMOOTH);
	gluQuadricTexture(g_quadratic1, GL_TRUE);

	g_quadratic2 = gluNewQuadric();//earth
	gluQuadricNormals(g_quadratic2, GLU_SMOOTH);
	gluQuadricTexture(g_quadratic2, GL_TRUE);

	g_quadratic3 = gluNewQuadric();//moon
	gluQuadricNormals(g_quadratic3, GLU_SMOOTH);
	gluQuadricTexture(g_quadratic3, GL_TRUE);

	image_t sun_image;
	image_t earth_image;
	image_t moon_image;

	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	tgaLoad("sun256128.tga", &sun_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	tgaLoad("earth_clouds256128.tga", &moon_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	tgaLoad("moon256128.tga", &earth_image, TGA_FREE | TGA_LOW_QUALITY);

	return true;
}

// Our Rendering Is Done Here
void render(void)   
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
	gluLookAt(0.0, 100.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, -100.0f);
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	gluSphere(g_quadratic1, 13.0f, 32, 32);
	glPopMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(40.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	gluSphere(g_quadratic2, 6.0f, 32, 32);
	glPopMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(15.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	gluSphere(g_quadratic2, 3.0f, 32, 32);
	angle += 0.2f;
    // Swap The Buffers To Become Our Rendering Visible
    glutSwapBuffers ( );
}

// Our Reshaping Handler (Required Even In Fullscreen-Only Modes)
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix
	glLoadIdentity();                // Reset The Projection Matrix
	// Calculate The Aspect Ratio And Set The Clipping Volume
	if (h == 0) h = 1;
	gluPerspective(80, (float)w/(float)h, 1.0, 5000.0);
	glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix
	glLoadIdentity();                // Reset The Modelview Matrix
}

// Our Keyboard Handler (Normal Keys)
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:        // When Escape Is Pressed...
			exit(0);    // Exit The Program
		break;          // Ready For Next Case
		default:        // Now Wrap It Up
		break;
	}
}

// Our Keyboard Handler For Special Keys (Like Arrow Keys And Function Keys)
void special_keys(int a_keys, int x, int y)
{
	switch (a_keys) {
		case GLUT_KEY_F1:
			// We Can Switch Between Windowed Mode And Fullscreen Mode Only
		break;
		default:
		break;
	}
}


// Main Function For Bringing It All Together.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);                           // GLUT Initializtion
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);     // Display Mode (Rgb And Double Buffered)
	glutInitWindowSize(500, 500);                // Window Size If We Start In Windowed Mode
	glutCreateWindow("NeHe's OpenGL Framework"); // Window Title 

	init();                                          // Our Initialization
	glutDisplayFunc(render);                         // Register The Display Function
	glutReshapeFunc(reshape);                        // Register The Reshape Handler
	glutKeyboardFunc(keyboard);                      // Register The Keyboard Handler
	glutSpecialFunc(special_keys);                   // Register Special Keys Handler
	glutIdleFunc(render);
	glutMainLoop();                                  // Go To GLUT Main Loop
	return 0;
}

