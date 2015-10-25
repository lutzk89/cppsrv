#ifndef DATAPROVIDER_H_
#define DATAPROVIDER_H_

#include<dbhandler.h>
#include<string>
class dataProvider {
	public:
	virtual int getLength();
	virtual int getDataset(int i);
};

class dirDataProvider: public dataProvider {
	private:
		dirDbhandler<double>* handler;
		char* dirName;
		static dirDataProvider* instanz;
		dirDataProvider();
	public:
		static dirDataProvider* getInstance();
		int read();
		double* getInput(int i);
		double* getOutput(int i);
		int getInputLength();
		int getOutputLength();
		int getNumOfSets();

};

#endif
