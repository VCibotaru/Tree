#include "node.h"
#include "tree.h"
#include <stdlib.h>
#include <algorithm> 

#define MAX_SLOTS 5


Node::Node(Tree *tr, int _s, int _m_s, bool Leaf, float _x, float _y, float _z, float s_x, float s_y, float s_z, float p, float t, Node *parent):
tree(tr),
slotBusy(MAX_SLOTS, false),
step(0),
slot(_s),
max_step(_m_s),
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
	if (step < max_step) {
		step++;
		scale_x += STEP_X; 
		scale_y += STEP_Y;
		scale_z += STEP_Z;
	}
	for (unsigned i = 0 ; i < children.size() ; ++i) {
		children[i].grow();
	}
	addChildren();

}

void Node::draw() {
	tree->drawNode(*this);
	for (unsigned i = 0 ; i < children.size() ; ++i) {
		children[i].draw();
	}
}

void Node::addChildren() {
	if (!tree->canAddBranch()){// && !tree->canAddLeaf()) {
		return;
	}
	bool leaf = false;
	int curSlot = findFreeSlot();
	if (curSlot < 0) {
		return;
	}
	float self_length = 2.0f;
	float slot_length = self_length / MAX_SLOTS;
	float newPhi = getRandomPhi();
	float newTheta = getRandomTheta();
	float t = slot_length * (curSlot + 0.5f);
/*	float newX = slot_length * sin(phi) * cos(theta) * (curSlot + 1/2);
	float newY = slot_length * sin(phi) * sin(theta) * (curSlot + 1/2);
	float newZ = slot_length * cos(phi) * (curSlot + 1/2);*/
	float newX = 
	std::cout << newX << " " << newY << std::endl;
	Node child(tree, curSlot, std::max(max_step - 40, 10), leaf, x + newX, y + newY, z + newZ, scale_x / 2, scale_y / 2, scale_z / 2, newPhi, newTheta, this);
	children.push_back(child);
	slotBusy[curSlot] = true;
}

int Node::findFreeSlot() {
	auto it = std::find(slotBusy.begin(), slotBusy.end(), false);
	if (it == slotBusy.end()) {
		return - 1;
	}
	while (1) {
		slot = rand() % MAX_SLOTS;
		if (slotBusy[slot] == false) {
			return slot;
		}
	}
}

int Node::getRandomPhi() {
	while (1) {
		int sign = rand() % 2;
		int angle = rand() % 180;
		angle = (sign) ? -angle : angle;
		if (angle + phi > 0 && angle + phi < 60) {
			return angle;
		}
	}
}

int Node::getRandomTheta() {
	return rand() % 360;
}

