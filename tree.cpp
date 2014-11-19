#include "tree.h"
#include "node.h"


const float THETA_INC = 0.3f;
const float PHI_INC = 0.3f;
Tree::~Tree() {
	delete pBranch;
	delete pLeaf;
	delete root;
	glDeleteTextures(2, texId);
}

void Tree::drawNodes() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	root->draw();
	glutSwapBuffers();
}

void Tree::grow() {
	root->grow();
}

void Tree::keyboard(unsigned char key, int mx, int my)
{
	if (key==' ') {
		useTexture = !useTexture;
	}
	switch (key) {
		case 'w':
			theta -= THETA_INC;
		break;
		case 's':
			theta += THETA_INC;
		break;
		case 'q':
			radius -= 1;
		break;
		case 'e':
			radius += 1;
		break;
		case 'a':
			phi -= PHI_INC;	
		break;
		case 'd':
			phi += PHI_INC;	
		break;
	}
	radius = (radius < 1) ? 1 : radius;
	/*theta = (theta < 0)    ? M_PI : theta;
	theta = (theta > M_PI) ? 0    : theta;
	phi = (phi < 0)        ? 2 * M_PI : phi;
	phi = (phi > 2 * M_PI) ? 0        : phi;*/

	
	float eyeX = radius * sin(phi);
	float eyeY = radius * sin(theta);
	float eyeZ = radius * cos(phi) * cos(theta);
	eye = glm::vec3(eyeX, eyeY, eyeZ);

}
void Tree::mouse(int button, int mode,int posx, int posy)
{
	if (button==GLUT_LEFT_BUTTON)
	{
		if (mode == GLUT_DOWN)
		{
			mouseX = posx; mouseY = posy;
		}
		else
		{
			mouseX = -1; mouseY = -1;
		}
	}
	
}






