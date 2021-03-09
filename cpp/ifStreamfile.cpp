#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(){
	string input_string;
	stringstream ss;
	ifstream inFile;
	inFile.open("input.txt");
	if(!inFile.open){
	cerr<<"Can't open the input file! ";
	}
	getline(inFile,input_string); // get a line from input file and store it to input_string as a string.
	ss.str(input_string); //Push string input to stringstream 
	//Push data from string string to the type responely.
	while(ss>>input_type){
		get++;
	}
	return 0;
}