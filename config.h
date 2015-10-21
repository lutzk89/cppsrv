class config {
	private:
		vector<string> key;
		vector<string> value;
		static const string delimiter;
	public:
		config(string cname) {
			string temp;
			string key, value;
			ifstream in(cname);
			while ( !in.eof() ) {
				in >> temp;
				if (! in.eof() ) {
					key = temp.substr(0, temp.find( this->delimiter ));
					value = temp.substr(temp.find( this->delimiter, temp.length() ));
					this->key.push_back(key);
					this->value.push_back(value);
				}
			}
		}
		string get(string key) {
			int ind = std::find( this->key.begin(), this->key.end(), key);
			if ( ind == this->key.end() ) {
				return "";
			}
			return value[ind];
		}
};
