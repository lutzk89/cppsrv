#include<dbhandler.h>
class dirDataProvider: public dataProvider {
	private:
	dirDbhandler* handler;
	char* dirName;
	public:
	dirDataProvider(char* dirName) {
		this->dirName = dirName;
		this->handler = new dirDbhandler<double>(this->dirname);
		this->handler->read_dir();
	}
	int read() {
		return 0;
	}
	double* getInput(int i) {

	}
	double *getOutput(int i) {

	}
	int getInputLength() {

	}
	int getOutputLength() {

	}
};
