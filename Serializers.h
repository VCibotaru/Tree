#include "node.h"
#include <fstream>


using namespace std;

struct nodeData
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
};

class Operation
{
	//templates may not be 'virtual' ???!!!
	virtual void DoOperation(fstream &file, unsigned &data) = 0;
	virtual void DoOperation(fstream &file, int &data) = 0;
	virtual void DoOperation(fstream &file, bool &data) = 0;
	virtual void DoOperation(fstream &file, float &data) = 0;
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


class Reader
{
	fstream file;
public:
	Reader(std::string fileName, ios_base::openmode mode) 
	: file(fileName, mode) {}
	~Reader() {
		file.close();
	}
	nodeData readNode();
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
	void write(Node &node);
};

class BinaryReader : public Reader
{
public:
	BinaryReader(std::string fileName) : Reader(fileName, 
		std::fstream::in | std::fstream::binary) {}
};


class BinaryWriter : public Writer
{
	fstream file;
public:
	bool InOut(Node & node);
	BinaryWriter(std::string fileName) : Writer(fileName, 
		std::fstream::out | std::fstream::binary) {}
};

class TextReader : public Reader
{
public:
	bool InOut(Node & node);
	TextReader(std::string fileName) : Reader(fileName, std::fstream::in) {}
};

class TextWriter : public Writer
{
	fstream file;
public:
	bool InOut(Node & node);
	TextWriter(std::string fileName) : Writer(fileName, std::fstream::out) {}
};
