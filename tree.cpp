#include "tree.h"
#include "node.h"


Tree::~Tree() {
	delete pBranch;
	delete pLeaf;
	delete root;
	glDeleteTextures(1,texId);
}

void Tree::drawNodes() {
	root->draw();
}

void Tree::grow() {
	root->grow();
}

void Tree::keyboard(unsigned char key, int mx, int my)
{
	if (key==' ') {
		useTexture = !useTexture;
	}
	if (key == 'g') {
	}
	if (key == 'a') {

	}
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






