
#include<string>
class dataProvider {
	public:
	virtual int getLength();
	virtual int getDataset(int i);
};

class dirDataProvider: public dataProvider {
	private:
		dirDbhandler* handler;
		char* dirName;
		static dirDataProvider* instanz;
		dirDataProvider() { };
	public:
		static dirDataProvider* getInstance() { }
		int read() { }
		double* getInput(int i) { }
		double* getOutput(int i) { }
		int getInputLength() { }
		int getOutputLength() { }
		int getNumOfSets() { }

};
