#ifndef NODE_H
#define NODE_H
//both for leaves and branches
#include <vector>
#include "tree.h"

class Tree;

class Node {
public:
	Node *parent;
	Tree *tree;
	std::vector<Node> children;
	float _x;
	float _y;
	float _z;
	float _height;
	float _width;
	float _length;
	float _phi;
	float _theta;
	bool isLeaf;
	
	Node(Tree *tr, float x, float y, float z, float h = 0.0f, float w = 0.0f, 
	 float l = 0.0f, float p = 0.0f, 
	 float t = 0.0f, Node *parent = 0, bool Leaf = false);

	void grow();
	void draw();

};

#endif