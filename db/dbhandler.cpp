#include<fstream>
#include<vector>

const int nnDataSet::filelength = 48;

template<class ntype>
class nnDataSet: public dataSet {
private:
	ntype* values;
	int length;
	ntype* input;
	ntype* output;
	int outLength;
	static const int filelength;
public:
	nnDataSet(char* fname) {
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
	ntype* getInput() {
		return this->input;
	}
	ntype* getOutput() {
		return this->output;
	}
	int getInputLength() {
		return this->filelength;
	}
	int getOutputLength() {
		return this->outLength;
	}
	int getLength() {
		return this->length;
	}
	ntype getValue(int position) {
		return this->values[position];
	}
	~nnDataSet() {
		delete[] this->values;
	}
};

class dbhandler {
};
template<class ntype>
class dirDbhandler: public dbhandler {
private:
	string dirName;
	vector<nnDataSet*> dataSets;
public:
	dirDbhandler(string dirName) {
		this->dirName = dirName;
	}
	int read_dir()
	{
		nnDataSet* newSet;
		int nfile=0;
		float temp;
		ifstream ifile;
		int i,j;
		char thisdir[] =        ".";
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

		ntype* getInput(int i) {

		}

		ntype* getOutput(int i) {

		}

		int getInputLength() {

		}

		int getOutputLength() {

		}

		return 0;
	}
};
