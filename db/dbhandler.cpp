
template<class ntype>
const int nnDataSet<ntype>::filelength = 48;

template<class ntype>
nnDataSet<ntype>::nnDataSet(char* fname) {
	ifstream ifile;
	vector<ntype> tvec;
	//its redefinition. Just make your own class if you dont like it...
	ifile.open(fname);
	ntype temp;
	this->length = 0;
	while ( !ifile.eof() ) {
		ifile >> temp;
		if ( !ifile.eof() ) {
			this->length++;
			tvec.push_back(temp);
		}
	}
	this->outLength = this->length - this->filelength;
	this->values = new ntype[this->length];
	this->input = new ntype[this->filelength];
	this->output = new ntype[this->outLength];
	int j=0;
	for ( vector<ntype>::iterator it = tvec.begin(); it != tvec.end() ; ++it) {
		this->values[j] = *it;
		if ( j < this->filelength ) {
			this->input[j] = *it;
		} else {
			this->output[j-this->filelength] = *it;
		}
		j++;
	}
	ifile.close();
	ifile.clear();
}
template<class ntype>
ntype* nnDataSet<ntype>::getInput() {
	return this->input;
}
template<class ntype>
ntype* nnDataSet<ntype>::getOutput() {
	return this->output;
}
template<class ntype>
int nnDataSet<ntype>::getInputLength() {
	return this->filelength;
}
template<class ntype>
int nnDataSet<ntype>::getOutputLength() {
	return this->outLength;
}
template<class ntype>
int nnDataSet<ntype>::getLength() {
	return this->length;
}
template<class ntype>
ntype nnDataSet<ntype>::getValue(int position) {
	return this->values[position];
}
template<class ntype>
nnDataSet<ntype>::~nnDataSet() {
	delete[] this->values;
}

template<class ntype>
dirDbhandler<ntype>::dirDbhandler(char* dirName) {
	this->dirName = dirName;
}
template<class ntype>
int dirDbhandler<ntype>::read_dir()
{
	nnDataSet* newSet;
	int nfile=0;
	float temp;
	ifstream ifile;
	int i,j;
	char thisdir[] = ".";
	char pardir[] = "..";
	char fullfile[100];
	DIR *dpdf;
	struct dirent *epdf;
	dpdf = opendir(dirName);
	if (dpdf != NULL){
		while ( ( epdf = readdir(dpdf) ) ){

			// std::out << epdf->d_name << std::endl;
			/*
			 * exclude . and ..
			 */
			if ( strcmp(epdf->d_name, thisdir) == 0 || strcmp(epdf->d_name, pardir) == 0 ) {
				continue;
			}
			//printf("Filename: %s",epdf->d_name);
		}
	}
	dpdf = opendir("./data");
	if (dpdf != NULL){
		while ( ( epdf = readdir(dpdf) ) ){

			// std::out << epdf->d_name << std::endl;
			/*
			 * exclude . and ..
			 */
			if ( strcmp(epdf->d_name, thisdir) == 0 || strcmp(epdf->d_name, pardir) == 0 ) {
				continue;
			}
			printf("Reading file: %s \n",epdf->d_name);
			j=0;
			for ( int k =0; k < 100; k++) {
				fullfile[k]='\0';
			}
			strcpy(fullfile,"./data/");
			strcat(fullfile,epdf->d_name);
			// insert dataset creation
			newSet = new nnDataSet<ntype>(fullfile);
			this->dataSets.push_back(newSet);
		}
	}
	return 0;
}
template<class ntype>
ntype* dirDbhandler<ntype>::getInput(int i) {
	if ( this->dataSets.size > i) {
		return->datSets[i].getInput(i);
	} else {
		return 0;
	}
}
template<class ntype>
ntype* dirDbhandler<ntype>::getOutput(int i) {
	if ( this->dataSets.size > i) {
			return->datSets[i].getOutput(i);
		} else {
			return 0;
		}
}
template<class ntype>
int dirDbhandler<ntype>::getInputLength() {
	if ( this->dataSets.size > 0 )
			return this->dataSets[0]->getInputLength();
		else
			return 0;
}
template<class ntype>
int dirDbhandler<ntype>::getOutputLength() {
	if ( this->dataSets.size > 0 )
		return this->dataSets[0]->getOutputLength();
	else
		return 0;
}
template<class ntype>
int dirDbhandler<ntype>::getNumOfSets() {
	return this->dataSets.size;
}


