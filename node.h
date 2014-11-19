#ifndef NODE_H
#define NODE_H
//both for leaves and branches
#include <vector>
#include "tree.h"

class Tree;

const float SCALE_X = 0.01f;
const float SCALE_Y = 1.0f;
const float SCALE_Z = 0.01f;
const float STEP_X = 0.000001f;
const float STEP_Y = 0.0001f;
const float STEP_Z = 0.00f;
const int MAX_STEP = 100;

class Node {
public:
	Node *parent;
	Tree *tree;
	std::vector<Node> children;
	std::vector<bool> slotBusy;
	int step;
	int slot;
	int max_step;
	bool isLeaf;
	float x;
	float y;
	float z;
	float scale_x;
	float scale_y;
	float scale_z;
	float phi;
	float theta;
	Node(Tree *tr, int _s, int _m_s, bool Leaf, float _x, float _y, float _z, float s_x = SCALE_X, float s_y = SCALE_Y, 
	 float s_z = SCALE_Z, float p = 0.0f, 
	 float t = 0.0f, Node *parent = 0);

	void grow();
	void draw();
	void addChildren();
	int findFreeSlot();
	int getRandomPhi();
	int getRandomTheta();
	glm::vec4 getBranchEnd(float t);
};

#endif