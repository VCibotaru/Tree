#include "tree.h"
#include "node.h"


const float THETA_INC = M_PI / 10.0f;
const float PHI_INC = M_PI / 10.0f;

Tree::~Tree() {
	delete pBranch;
	delete pLeaf;
	delete root;
	glDeleteTextures(2, texId);
}

void Tree::drawNodes() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if (swing) {
		//root->phi = 1.0f * currentSwing;
		root->updateModelMatrix();
	}
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
		return;
	}
	if (key == 'z') {
		root->phi = 0.0f;
		swing = !swing;
		return;
	}
	if (key == 'e') {
		if (radius > 0.5f) {
			radius -= 0.5f;
			eye = cen + radius * glm::normalize(eye - cen);
		}
		return;
	}
	if (key == 'q') {
		radius += 0.5f;
		eye = cen + radius * glm::normalize(eye - cen);
		return;
	}
	switch (key) {
		case 'w':
			if (theta - THETA_INC < - M_PI / 2) {
				return;
			}
			theta -= THETA_INC;
		break;
		case 's':
			if (theta + THETA_INC > M_PI / 2) {
				return;
			}
			theta += THETA_INC;
		break;
		case 'a':
			phi -= PHI_INC;	
		break;
		case 'd':
			phi += PHI_INC;	
		break;
	}
	
	float eyeX = cen.x + radius * sin(phi);
	float eyeY = cen.y + radius * sin(theta);
	float eyeZ = cen.z + radius * cos(phi) * cos(theta);
	eye = glm::vec3(eyeX, eyeY, eyeZ);

}
void Tree::mouse(int button, int mode, int posx, int posy)
{
	if (button==GLUT_LEFT_BUTTON) {
		if (mode == GLUT_DOWN) {
			if (radius > 2.0f) {
				radius -= 2.0f;
				eye -= 2.0f * glm::normalize(eye - cen);
			}
		}
		else {
			mouseX = -1; mouseY = -1;
		}
	}

	if (button == GLUT_RIGHT_BUTTON) {
		if (mode == GLUT_DOWN) {
			radius += 2.0f;
			eye += 2.0f * glm::normalize(eye - cen);
		}
		else {
			mouseX = -1; mouseY = -1;
		}
	}
}

void Tree::passiveMouse(int posx, int posy)
{
	dir = glm::normalize(cen - eye);
	rDir = glm::cross(dir, up);
	h = float(glutGet(GLUT_WINDOW_WIDTH) / 2 - posx) * 0.0003 * mTime;
	float vOffset = float(glutGet(GLUT_WINDOW_HEIGHT) / 2 - posy) * 0.0003 * mTime;
	if (v + vOffset > 0 && v + vOffset < 45.0f) {
		v += vOffset;
	} else {
		vOffset = 0.0f;
	}

	glm::mat4 rotationMat(1);
	rotationMat = glm::rotate(rotationMat, h, up);
	dir = glm::vec3(rotationMat * glm::vec4(dir, 1.0));
	rDir = glm::vec3(rotationMat * glm::vec4(rDir, 1.0));

	rotationMat = glm::mat4(1);
	rotationMat = glm::rotate(rotationMat, vOffset, rDir);
	dir = glm::vec3(rotationMat * glm::vec4(dir, 1.0));

	if ((radius * glm::normalize(dir) + eye).y > 0) {
		cen = radius * glm::normalize(dir) + eye;
	}
	radius = sqrt((cen.x - eye.x) * (cen.x - eye.x) + (cen.y - eye.y) * (cen.y - eye.y) + (cen.z - eye.z) * (cen.z - eye.z));
	mouseX = posx;
	mouseY = posy;
}







