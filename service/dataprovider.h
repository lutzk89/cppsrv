
class dataProvider {
	public:
	virtual int getLength();
	virtual int getDataset(int i);
}

class dirDataProvider: public dataProvider {
	private:
	dbhandler* handler;
	string dirName;
	public:
	dirDataProvider(string dirName) {
		this->dirName = dirName;
		handler = new dbhandler();
		handler->read_dir(dirName);
	}
	int read() {
	}
}
