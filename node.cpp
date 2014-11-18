#include "node.h"
#include "tree.h"



Node::Node(Tree *tr, bool Leaf, float _x, float _y, float _z, float s_x, float s_y, float s_z, float p, float t, Node *parent):
tree(tr),
step(0),
isLeaf(Leaf),
x(_x),
y(_y),
z(_z),
scale_x(s_x),
scale_y(s_y),
scale_z(s_z),
phi(p),
theta(t)
{
	if (Leaf) {
		tree->incLeaves();
	}
	else {
		tree->incBranches();
	}
}

void Node::grow() {
	if (isLeaf) {
		return;
	}
	if (step < MAX_STEP) {
		step++;
		scale_x += STEP_X; 
		scale_y += STEP_Y;
		scale_z += STEP_Z;
	}
	for (Node child : children) {
		child.grow();
	}
	addChildren();

}


void Node::draw() {

	tree->drawNode(*this);
}