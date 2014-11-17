#include "node.h"
#include "tree.h"



Node::Node(Tree *tr,float x, float y, float z, float h, float w, float l, float p, float t, Node *parent, bool Leaf):
tree(tr),
_x(x),
_y(y),
_z(z),
_height(h),
_width(w),
_length(l),
_phi(p),
_theta(t), 
isLeaf(Leaf)
{
}

void Node::grow() {

}


void Node::draw() {
	tree->drawNode(*this);
}