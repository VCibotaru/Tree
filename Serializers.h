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
	virtual ~Operation() = 0;
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
	virtual ~ReadOperation() {};
};

class WriteOperation
{
public:
	virtual void DoOperation(fstream &file, unsigned &data) {
		file << data << " ";
	}
	virtual void DoOperation(fstream &file, int &data) {
		file << data << " ";
	}
	virtual void DoOperation(fstream &file, bool &data) {
		file << data << " ";
	}
	virtual void DoOperation(fstream &file, float &data) {
		file << data << " ";
	}
	virtual ~WriteOperation() {};
};

class BinaryReadOperation
{
public:
	virtual void DoOperation(fstream &file, unsigned &data) {
		for (unsigned size = 0, data = 0; size < sizeof(data); ++size) {
			data |= file.get() << (8 * size);
		}
	}
	virtual void DoOperation(fstream &file, int &data) {
		for (unsigned size = 0, data = 0; size < sizeof(data); ++size) {
			data |=file.get() << (8 * size);
		}
	}
	virtual void DoOperation(fstream &file, bool &data) {
		for (unsigned size = 0, data = 0; size < sizeof(data); ++size) {
			data |= file.get() << (8 * size);
		}
	}
	virtual void DoOperation(fstream &file, float &data) {
		int *fData = (int *) &data;
		for (unsigned size = 0, data = 0; size < sizeof(*fData); ++size) {
			*fData |= file.get() << (8 * size);
		}
	}
	virtual ~BinaryReadOperation() {};
};

class BinaryWriteOperation
{
public:
	virtual void DoOperation(fstream &file, unsigned &data) {
		for (unsigned size = sizeof(data); size; --size, data >>= 8) {
			file.put( static_cast <char> (data & 0xFF) );
		}
	}
	virtual void DoOperation(fstream &file, int &data) {
		for (unsigned size = sizeof(data); size; --size, data >>= 8) {
			file.put( static_cast <char> (data & 0xFF) );
		}
	}
	virtual void DoOperation(fstream &file, bool &data) {
		for (unsigned size = sizeof(data); size; --size, data >>= 8) {
			file.put( static_cast <char> (data & 0xFF) );
		}
	}
	virtual void DoOperation(fstream &file, float &data) {
		int *fData = (int *) &data;
		for (unsigned size = sizeof(*fData); size; --size, *fData >>= 8) {
			file.put( static_cast <char> (*fData & 0xFF) );
		}
	}
	virtual ~BinaryWriteOperation() {};
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

#define BINARY_READ  std::fstream::in  | std::fstream::binary
#define BINARY_WRITE std::fstream::out | std::fstream::binary
#define TEXT_READ    std::fstream::in                        
#define TEXT_WRITE   std::fstream::out 

class Reader
{
	fstream file;
	ios_base::openmode mode;
public:
	Reader(std::string fileName, ios_base::openmode m) : mode(m) {
		file.open(fileName, mode);
	}
	~Reader() {
		file.close();
	}
	NodeData readNode();
	void readModel(Node &root);

};

class Writer
{
	fstream file;
	ios_base::openmode mode;
public:
	Writer(std::string fileName, ios_base::openmode m) : mode(m) {
		file.open(fileName, mode);
	}
	~Writer() {
		file.close();
		std::cout << "File closed" << std::endl;
	}
	void writeNode(Node &node);
	void writeModel(Node &root);
};