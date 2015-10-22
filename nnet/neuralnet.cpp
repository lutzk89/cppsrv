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
		int numOfLayers = this->getNumOfLayers();
		int sizeW = this->getSizeOfW();
		int sizeB = this->getSizeOfB();
		this->w = new double[sizeW];
		this->b = new double[sizeB];
	}

	neuralnet(const neuralnet &other) {
		this->nin = other.nin;
		this->nout = other.nout;
		this->nhi = other.nhi;
		this->provider = other.provider;
		int sizeW = this->getSizeOfW();
		int sizeB = this->getSizeOfB();
		this->w = new double[sizeW];
		this->b = new double[sizeB];
		std::copy(other.w,other.w+sizeW * sizeof( double ),this->w);
		std::copy(other.b,other.b+sizeB * sizeof( double ),this->b);
	}
	/*
	 * Gewichte und Bias random initialisieren
	 */
	int randomInit() {
		return 0;
	}

	int getNumOfLayers() {
		return this->nhi + 2;
	}

	int getSizeOfW() {
		return this->nin * this->nin * this->getNumOfLayers();
	}

	int getSizeOfB() {
		return this->nin * this->getNumOfLayers();
	}
	/*
	 * Einzelner Datensatz Feedforward, i ist index für provider
	 */
	int feedForward(int i) {
		return 0;
	}
	/*
	 * Alle Datensätze Feedforward und anschliessender Backprop
	 *  s : Stopping Criterion
	 */
	int backprop(double s) {
		return 0;
	}
};
