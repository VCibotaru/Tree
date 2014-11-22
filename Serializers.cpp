#include "Serializers.h"

using namespace std;


nodeData::nodeData(fstream file) {
	file >> childrenCount;
	file >> step;
	file >> slot;
	file >> max_step;
	file >> isLeaf;
	file >> scale_x;
	file >> scale_y;
	file >> scale_z;
	file >> phi;
	file >> theta;
	file >> height;
}

nodeData Reader::readNode() {
	
}

void nodeData::writeToFile(fstream file) {
	
}

void Reader::readModel(Node &root) {
	
}


void Writer::write(Node &node) {
	
}