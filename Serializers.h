#include "node.h"
#include <fstream>


using namespace std;


class Operation
{
public:
	//templates may not be 'virtual' ???!!!
	virtual void DoOperation(fstream &file, unsigned &data) = 0;
	virtual void DoOperation(fstream &file, int &data) = 0;
	virtual void DoOperation(fstream &file, bool &data) = 0;
	virtual void DoOperation(fstream &file, float &data) = 0;
	virtual ~Operation();
};

class ReadOperation
{
public:
	virtual void DoOperation(fstream &file, unsigned &data) {
		file >> data;
	}
	virtual void DoOperation(fstream &file, int &data) {
		file >> data;
	}
	virtual void DoOperation(fstream &file, bool &data) {
		file >> data;
	}
	virtual void DoOperation(fstream &file, float &data) {
		file >> data;
	}
};

class WriteOperation
{
public:
	virtual void DoOperation(fstream &file, unsigned &data) {
		file << data;
	}
	virtual void DoOperation(fstream &file, int &data) {
		file << data;
	}
	virtual void DoOperation(fstream &file, bool &data) {
		file << data;
	}
	virtual void DoOperation(fstream &file, float &data) {
		file << data;
	}
};

enum ProcessMode {
	READ_FILE,
	WRITE_FILE
};

struct NodeData
{
	unsigned childrenCount;
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

	NodeData() {};
	NodeData(Node &node);
	void processFile(fstream &file, enum ProcessMode mode);
};

enum FileMode {
	BINARY_READ  = std::fstream::in  | std::fstream::binary,
	BINARY_WRITE = std::fstream::out | std::fstream::binary,
	TEXT_READ    = std::fstream::in                        ,
	TEXT_WRITE   = std::fstream::out 
};

class Reader
{
	fstream file;
public:
	Reader(std::string fileName, ios_base::openmode mode) 
	: file(fileName, mode) {}
	~Reader() {
		file.close();
	}
	NodeData readNode();
	void readModel(Node &root);

};

class Writer
{
	fstream file;
public:
	Writer(std::string fileName, ios_base::openmode mode) 
	: file(fileName, mode) {}
	~Writer() {
		file.close();
	}
	void writeNode(Node &node);
	void writeModel(Node &root);
};