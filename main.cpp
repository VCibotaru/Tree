//standard libraries
#include <iostream>
using namespace std;

//opengl headers
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

//opengl mathematics
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

//functions for shader compilation and linking
#include "shaderhelper.h"
//object for drawing
#include "Branch.h"
#include "Leaf.h"
#include "tree.h"

Tree tree;


void reshape(int width, int height) {
  tree.reshape(width, height);
}

void display()
{
  tree.mTime = glutGet(GLUT_ELAPSED_TIME) - tree.cTime;
  tree.cTime = glutGet(GLUT_ELAPSED_TIME);
  tree.drawNodes();
}

void timerFunc(int data) {
  if (tree.swing) {
    static int direction = 1;
    tree.currentSwing += direction;
    if (tree.currentSwing == -SWINGS || tree.currentSwing == SWINGS ) {
      direction = -direction;
    }
  }
  tree.grow();
  glutPostRedisplay();
  glutTimerFunc(100, timerFunc, 1);
}

void update()
{
	//make animation
	glutPostRedisplay();
}


/////////////////////////////////////////////////////////////////////////
///is called when key on keyboard is pressed
///use SPACE to switch mode
///TODO: place camera transitions in this function
void keyboard(unsigned char key, int mx, int my)
{
  tree.keyboard(key, mx, my);
}

/////////////////////////////////////////////////////////////////////////
///is called when mouse button is pressed
///TODO: place camera rotations in this function
void mouse(int button, int mode,int posx, int posy)
{
  tree.mouse(button, mode, posx, posy);

}

void passiveMouse(int posx, int posy) {
  tree.passiveMouse(posx, posy);
}

////////////////////////////////////////////////////////////////////////
///this function is used in case of InitializationError
void emptydisplay()
{
}

////////////////////////////////////////////////////////////////////////
///entry point
int main (int argc, char* argv[])
{
  tree.windowWidth = 800;
  tree.windowHeight = 600;
  glutInit(&argc, argv);
#ifdef __APPLE__
  glutInitDisplayMode( GLUT_3_2_CORE_PROFILE| GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#else
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitContextVersion (3, 2);  
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextFlags (GLUT_FORWARD_COMPATIBLE);
#endif
  glewExperimental = GL_TRUE;
  glutCreateWindow("Test OpenGL application");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutReshapeWindow(tree.windowWidth,tree.windowHeight);
  glutIdleFunc(update);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passiveMouse);
  glutTimerFunc(100, timerFunc, 0);

  glewInit();
  const char * slVer = (const char *) glGetString ( GL_SHADING_LANGUAGE_VERSION );
  cout << "GLSL Version: " << slVer << endl;

  try
  {
   tree.init();
 }
 catch (const char *str)
 {
   cout << "Error During Initialiation: " << str << endl;
   glutDisplayFunc(emptydisplay);
   glutMainLoop();
   return -1;
 }


 try
 {
   glutMainLoop();
 }
 catch (const char *str)
 {
   cout << "Error During Main Loop: " << str << endl;
 }
 return 0;
}
