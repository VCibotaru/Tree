#include "Serializers.h"

using namespace std;

NodeData::NodeData(Node &node) {
	childrenCount = node.children.size();
	step          = node.step;
	slot          = node.slot;
	max_step      = node.max_step;
	isLeaf        = node.isLeaf;
	scale_x       = node.scale_x;
	scale_y       = node.scale_y;
	scale_z       = node.scale_z;
	phi           = node.phi;
	theta         = node.theta;
	height        = node.height;
}

void NodeData::processFile(fstream &file, ProcessMode mode) {
	Operation *op;
	if (mode == READ_FILE) {
		op = (Operation *) new ReadOperation;
	}
	else if (mode == WRITE_FILE) {
		op = (Operation *) new WriteOperation;
	}
	else {
		std::cout << "Unknown operation type" << std::endl;
		return;
	}
	op->DoOperation(file, childrenCount);
	op->DoOperation(file, step);
	op->DoOperation(file, slot);
	op->DoOperation(file, max_step);
	op->DoOperation(file, isLeaf);
	op->DoOperation(file, scale_x);
	op->DoOperation(file, scale_y);
	op->DoOperation(file, scale_z);
	op->DoOperation(file, phi);
	op->DoOperation(file, theta);
	op->DoOperation(file, height);
	delete op;
}


NodeData Reader::readNode() {
	NodeData result;
	result.processFile(file, READ_FILE);
	return result;
}

void Reader::readModel(Node &root) {
	
}


void Writer::writeNode(Node &node) {
	
}

void Writer::writeModel(Node &root) {

}