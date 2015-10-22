
#include<string>
class dataProvider {
	public:
	virtual int getLength();
	virtual int getDataset(int i);
};

class dirDataProvider: public dataProvider {
	private:
		dirDbhandler* handler;
		string dirName;
	public:
		dirDataProvider(string dirName) { }
		int read() { }
};
