#include "node.h"
#include "tree.h"
#include <stdlib.h>
#include <algorithm> 

#define MAX_SLOTS 5


Node::Node(Tree *tr, bool Leaf, float _x, float _y, float _z, float s_x, float s_y, float s_z, float p, float t, Node *parent):
tree(tr),
slotBusy(MAX_SLOTS, false),
step(0),
slot(-1),
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
		std::cout << child.y << std::endl;
		child.grow();
	}
	addChildren();

}

void Node::draw() {
	tree->drawNode(*this);
	for (Node child : children) {
		child.draw();
	}
}

void Node::addChildren() {
	if (!tree->canAddBranch()) {
		return;
	}
	std::cout << "Adding children" << std::endl;
	int curSlot = findFreeSlot();
	if (curSlot < 0) {
		//all slots are busy
		return;
	}
	std::cout << "Slot found " << curSlot << std::endl;
	float self_length = 2.0f;
	float slot_length = self_length / MAX_SLOTS;
	//grow new branch at half of needed slot
	float newY = curSlot * slot_length + slot_length / 2;
	std::cout << "New child at: " << x << " " << newY + y << " " << z << std::endl; 
	Node child(tree, false, x, y + newY, z, SCALE_X, SCALE_Y, SCALE_Z, 45.0f, 0.0f, this);
	children.push_back(child);
	std::cout << "Child pushed" << std::endl;
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

