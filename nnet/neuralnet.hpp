class neuralnet {
	private:
	double* w;
	double* b;
	int nin;
	int nout;
	int nhi;
	dataProvider* provider;
	public:
	neuralnet(int newNin, int newNout, int newNhi,dataProvider* provider) {
		this->nin = newNin;
		this->nout = newNout;
		this->nhi = newNhi;
		this->provider = provider;
	}
	
	int backprop() {
	}
}
