#ifndef TREE_H
#define TREE_H

#include <iostream>

#include <vector>
#include "Branch.h"
#include "Leaf.h"
#include "node.h"

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

const unsigned int MAX_BRANCHES = 3000;
const unsigned int MAX_LEAVES = 10000;
const float ROOT_TRANS_X = 0.0f;
const float ROOT_TRANS_Y = 0.0f;
const float ROOT_TRANS_Z = 0.0f;


class Node;

class Tree {
	Node *root;
	unsigned int branches, leaves;
	ShaderProgram shaderProgram;
	Branch* pBranch;
	Leaf* pLeaf;
	bool useTexture;
	GLuint texId[2];
	glm::mat4x4 projectionMatrix;
	int mouseX, mouseY;
	glm::vec3 eye;
	glm::vec3 cen;
	glm::vec3 up;
	float phi, theta, radius;

public:
	int windowWidth;
	int windowHeight;
	~Tree();
	void grow();
	void drawNodes();
	void addNewNodes();
	void drawNode(Node &node);
	void init();
	void initTexture();
	void reshape(int width, int height);
	void keyboard(unsigned char key, int mx, int my);
	void mouse(int button, int mode,int posx, int posy);
	void incBranches() {
		branches++;
	}
	void incLeaves() {
		leaves++;
	}
	bool canAddBranch() {
		return (branches < MAX_BRANCHES);
	}
};

#endif