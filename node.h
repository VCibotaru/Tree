#ifndef NODE_H
#define NODE_H
//both for leaves and branches
#include <vector>
#include "tree.h"

class Tree;

const float SCALE_X = 0.01f;
const float SCALE_Y = 1.0f;
const float SCALE_Z = 0.01f;
const float STEP_X = 0.00001f;
const float STEP_Y = 0.0001f;
const float STEP_Z = 0.00f;
const int MAX_STEP = 100;

class Node {
public:
	Tree *tree;
	std::vector<Node> children;
	std::vector<bool> slotBusy;
	int step;
	int slot;
	int max_step;
	bool isLeaf;
	float scale_x;
	float scale_y;
	float scale_z;
	float phi;
	float theta;
	float height;
	Node *parent;
	glm::mat4x4 modelMatrix;
	glm::mat4x4 initialMatrix;
	Node(Tree *tr, int _s, int _m_s, bool Leaf, float s_x = SCALE_X, float s_y = SCALE_Y, 
	 float s_z = SCALE_Z, float p = 0.0f, 
	 float t = 0.0f, float h = 0.0f, Node *_parent = 0);

	void grow();
	void draw();
	void addChildren();
	int findFreeSlot();
	int getRandomPhi();
	int getRandomTheta();
	void updateModelMatrix();
	glm::mat4x4 getModelMatrix(); 
};

#endif