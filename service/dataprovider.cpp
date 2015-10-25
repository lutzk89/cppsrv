#include<dbhandler.h>
dirDataProvider* dirDataProvider::instanz = 0;
dirDataProvider::dirDataProvider() {
	this->dirName = '../forex_work/data'; // TODO aus config holen
	this->handler = new dirDbhandler<double>(this->dirName);
	this->handler->read_dir();
}
static dirDataProvider* dirDataProvider::getInstance() {
	if ( instanz == 0 ) {
		instanz = new dirDataProvider();
	}
	return instanz;
}
int dirDataProvider::read() {
	return 0;
}
double* dirDataProvider::getInput(int i) {

}
double* dirDataProvider::getOutput(int i) {

}
int dirDataProvider::getInputLength() {

}
int dirDataProvider::getOutputLength() {

}
int dirDataProvider::getNumOfSets() {
	return this->handler->getNumOfSets();
}
