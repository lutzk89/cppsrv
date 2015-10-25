/*
 * dbhandler.h
 *
 *  Created on: 21.10.2015
 *      Author: lutzk
 */

#ifndef DB_DBHANDLER_H_
#define DB_DBHANDLER_H_
#include<vector>
#include<fstream>


template<class ntype>
class dataSet {
public:
	virtual int getLength();
	virtual ntype getValue(int position);
};

template<class ntype>
class nnDataSet: public dataSet<ntype> {
private:
	ntype* values;
	int length;
	ntype* input;
	ntype* output;
	int outLength;
	static const int filelength;
public:
	nnDataSet(char* fname);
	~nnDataSet();
	ntype* getInput();
	ntype* getOutput();
	int getInputLength();
	int getOutputLength();
	int getLength();
	ntype getValue(int position);

};

class dbhandler {
};
template<class ntype>
class dirDbhandler: public dbhandler {
private:
	char* dirName;
	vector<nnDataSet<ntype>*> dataSets;
public:
	dirDbhandler(char* dirName);
	int read_dir();
	ntype* getInput(int i);
	ntype* getOutput(int i);
	int getInputLength();
	int getOutputLength();
	int getNumOfSets();
};



#endif /* DB_DBHANDLER_H_ */
