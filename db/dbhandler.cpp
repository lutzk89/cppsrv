template<class ntype>
class nnDataSet: public dataSet {
        private:
            ntype* values;
            int length;
        public:
            nnDataSet(string fname) {
			ifstream ifile;
			vector<ntype> tvec;
			int j=0;
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
			this->values = new ntype[this->length];
			for ( vector<ntype>::iterator it = tvec.begin(); it != tvec.end() ; ++it) {
				this->values[j] = *it;
				j++;
			}
                        ifile.close();
                        ifile.clear();
                }
                int getLength() {
                        return this->length;
                }
                ntype getValue(int position) {
                        return this->values[position];
                }
}

class dbhandler {
}

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
		nfile=0;
                flength=filelength;
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
                                nfile++;
                        }
                }
                this->fbuf = new float[nfile*flength];
                dpdf = opendir("./data");
                i=0;
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
                                i++;
                        }
                }


	}
}
