#include "node.h"
#include "tree.h"
#include <stdlib.h>
#include <algorithm> 

#define MAX_SLOTS 10

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
	int curSlot = findFreeSlot();
	if (curSlot < 0) {
		return;
	}
	float newPhi = getRandomPhi();
	float newTheta = getRandomTheta();
	float t = curSlot * 1.0f / (MAX_SLOTS + 1) + 0.1f;
	glm::vec4 end = getBranchEnd(t);
	if (tree->canAddBranch()) {
		Node child(tree, curSlot, max_step, false, end.x, end.y, end.z, scale_x / 2, scale_y / 2, scale_z / 2, newPhi, newTheta, this);
		children.push_back(child);
		slotBusy[curSlot] = true;
	}
	else {
		const float LEAF_SCALE = 0.02f;
		Node child(tree, curSlot, max_step, true, end.x, end.y, end.z, LEAF_SCALE, LEAF_SCALE, LEAF_SCALE, newPhi, newTheta, this);
		children.push_back(child);
		slotBusy[curSlot] = true;
	}
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
		if (angle + phi > 0 && angle + phi < 90) {
			return angle;
		}
	}
}

int Node::getRandomTheta() {
	const int delta = 30;
	int sector = rand() % 10;
	return delta * sector;
}

glm::vec4 Node::getBranchEnd(float t) {
	glm::mat4x4 modelMatrix = glm::mat4();

	modelMatrix = glm::translate(modelMatrix,glm::vec3(x, y, z));
	modelMatrix = glm::rotate(modelMatrix, theta, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, phi, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix,glm::vec3(scale_x, scale_y, scale_z));

	return modelMatrix * glm::vec4(0.0f, t, 0.0f, 1.0f);
}
