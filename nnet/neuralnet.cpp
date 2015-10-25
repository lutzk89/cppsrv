
static const double one = 1.0;
static const double two = 2.0;

neuralnet::neuralnet(int newNin, int newNout, int newNhi) {
	this->learningRate = 1.0;
	this->nin = newNin;
	this->nout = newNout;
	this->nhi = newNhi;
	this->provider = dirDataProvider::getInstance();
	this->nsets = provider->getNumOfSets();
	int numOfLayers = this->getNumOfLayers();
	int sizeW = this->getSizeOfW();
	int sizeB = this->getSizeOfB();
	int sizeZ = this->getSizeOfZ();
	this->w = new double[sizeW];
	this->b = new double[sizeB];
	this->d = new double[sizeZ];
	this->z = new double[sizeZ];
	this->a = new double[sizeZ];
}
neuralnet::neuralnet(const neuralnet &other) {
	this->learningRate = other.learningRate;
	this->nin = other.nin;
	this->nout = other.nout;
	this->nhi = other.nhi;
	this->provider = other.provider;
	this->nsets = provider->getNumOfSets();
	int sizeW = this->getSizeOfW();
	int sizeB = this->getSizeOfB();
	int sizeZ = this->getSizeOfZ();
	this->w = new double[sizeW];
	this->b = new double[sizeB];
	this->z = new double[sizeZ];
	this->a = new double[sizeZ];
	this->d = new double[sizeZ];
	std::copy(other.w,other.w+sizeW * sizeof( double ),this->w);
	std::copy(other.b,other.b+sizeB * sizeof( double ),this->b);
}
neuralnet::~neuralnet() {
	delete[] this->w;
	delete[] this->b;
	delete[] this->z;
	delete[] this->a;
	delete[] this->d;
}
/*
 * Gewichte und Bias random initialisieren
 */
int neuralnet::randomInit() {
	  std::default_random_engine generator;
	  std::normal_distribution<double> distribution(0.1,0.1);
	  for ( int i = 0 ; i < this->getSizeOfW(); i++ ) {
		  this->w[i] = distribution(generator);
	  }
	  for ( int i = 0; i < this->getSizeOfB(); i++ ) {
		  this->b[i] = distribution(generator);
	  }
	return 0;
}
/*
 * mutieren
 */
int neuralnet::randomInit() {
	  std::default_random_engine generator;
	  std::normal_distribution<double> distribution(0.0,0.2);
	  for ( int i = 0 ; i < this->getSizeOfW(); i++ ) {
		  this->w[i] += distribution(generator);
	  }
	  for ( int i = 0; i < this->getSizeOfB(); i++ ) {
		  this->b[i] += distribution(generator);
	  }
	return 0;
}

int neuralnet::getNumOfLayers() {
	return this->nhi + 2;
}

int neuralnet::getSizeOfW() {
	return this->nin * this->nin * this->getNumOfLayers();
}

int neuralnet::getSizeOfB() {
	return this->nin * this->getNumOfLayers();
}
int neuralnet::getSizeOfZ() {
	return this->getSizeOfB() * this->nsets;
}
int neuralnet::getBaddress(int node,int layer) {
	return layer * this->nin + node;
}
int neuralnet::getZaddress(int node,int layer,int dataset) {
	return dataset*this->nin*this->getNumOfLayers() + layer*this->nin + node;
}

int neuralnet::getWaddress(int node1,int node2,int layer) {
	return layer * this->nin * this->nin + node1 * this->nin + node2;
}
/*
 * Einzelner Datensatz Feedforward, i ist index für provider
 * Ermittelt z, a, d sowie totalen Fehler für geg. Datensatz
 */
double neuralnet::feedForward(int dset) {
	double* input = provider->getInput(dset);
	double* output = provider->getOutput(dset);
	int inLength = provider->getInputLength();
	int outLength = provider->getOutputLength();
	int address;
	int paddress;
	int waddress;
	int baddress;
	double error;

	for ( int i = 0; i < this->getNumOfLayers(); i++ ) {
		for ( int j = 0 ; j < this->nin; j++) {
			address = this->getZaddress(j,i,dset);
			baddress = this->getBaddress(j,i);
			this->d[address] = 0;
			if ( i == 0 ) {
				this->z[address] = input[j] + this->b[baddress];
			} else {
				this->z[address] = this->b[address];
				for ( int k = 0; k < this->nin; k++ ) {
					waddress = this->getWaddress(j,k,i);
					this->z[address] +=  this->w[waddress];
				}
			}
			this->a[address] = this->propFunc(this->z[address]);
			if ( i == this->nin - 1 && j < outLength ) {
				error = error + (this->a[address] - output[j]) * (this->a[address] - output[j]);
				this->d[address] = ( this->a[address] - output[j] ) * this->propFuncPrime(this->z[address]);
			}
		}
	}
	for ( int i = this->getNumOfLayers() - 2; i >= 0; i--) {
		for ( int j = 0 ; j < this->nin; j++ ){
			int address = this->getZaddress(j,i,dset);
			for ( int k = 0; k < this->nin; k++) {
				int paddress = this->getZaddress(k,i+1,dset);
				int waddress(k,j,i+1);
				this->d[address] += this->w[waddress] * d[paddress];
			}
			this->d[address] *= this->propFuncPrime(this->z[address]);
		}
	}
	return error;
}

int neuralnet::gradientStep(int dset) {
	double normalization = this->learningRate / ((double)(this->nin * this->nin));
	int address, baddress, waddress, aaddress;
	for ( int i = 0; i < this->getNumOfLayers(); i++) {
		for ( int j = 0; j < this->nin ; j++ ) {
			address = this->getZadress(j,i,dset);
			baddress = this->getBadress(j,i,dset);
			this->b[baddress] -= this->d[address] * normalization;
			if ( i == 0 )
				continue;
			for ( int k = 0; k < this->nin; k++) {
				waddress = this->getWadress(j,k,i);
				aaddress = this->getZaddress(k,i-1,dset);
				this->w[waddress] -= this->d[address] * this->a[aaddress] * normalization;
			}
		}
	}
	return 0;
}
/*
 * Alle Datensätze Feedforward und anschliessender Backprop
 *  s : Stopping Criterion
 */
double neuralnet::backprop(double s) {
	double errFull = two * s;
	int maxIt = 1000;
	int iteration = 0;
	while ( errFull > s && iteration < maxIt ) {
		iteration++;
		errFull = 0;
		for ( int i = 0; i < this->nsets; i++) {
			errFull += this->feedForward(i);
		}
		for ( int i = 0; i < this->nsets; i++) {
			this->gradientStep(i);
		}
	}
	return errFull;
}
double neuralnet::propFunc(double x) {
	return one / ( one + exp(-x ));
}
double neuralnet::propFuncPrime(double x) {
	return exp(-x)/((one - exp(-x))*(one - exp(-x)));
}
