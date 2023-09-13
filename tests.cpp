#include <iostream>
// #include "bar.h"
// #include "barchart.h"
#include "barchartanimate.h"
#include<sstream>
using namespace std;

// bar.h tests

bool testBarDefaultConstructor() {

	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {

	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarGetName(){

	Bar b("Chicago", 9234324, "US");
	if (b.getName() != "Chicago") {
		cout << "testBarParamConstructor: getName failed" << endl;
		return false;
	} 
	cout << "testBarGetName passed!" << endl;
	return true;
}

bool testBarGetValue(){

	Bar b("Chicago", 9234324, "US");
	if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } 
	cout << "testBarGetValue passed!" << endl;
	return true;
}

bool testBarGetCategory(){

	Bar b("Chicago", 9234324, "US");
	if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
	cout << "testBarGetCategory passed!" << endl;
	return true;
}

bool operatorLessThan(){

	Bar b1("a", 1, "cat");
	Bar b2("b", 2, "cat");
	if(b1 < b2){	
		cout << "operatorLessThan passed!" << endl;
		return true;
	}
	else{
		cout << "operatorLessThan failed!" << endl;
		return false;
	}
}

bool operatorMoreThan(){

	Bar b1("a", 1, "cat");
	Bar b2("b", 2, "cat");
	if(b2 > b1){	
		cout << "operatorMoreThan passed!" << endl;
		return true;
	}
	else{
		cout << "operatorMoreThan failed!" << endl;
		return false;
	}
}

bool operatorLessThanOrEqualTo()
{
	Bar b1("a", 1, "cat");
	Bar b2("b", 2, "cat");
	if(b1 <= b2){	
		cout << "operatorLessThanOrEqualTo passed!" << endl;
		return true;
	}
	else
	{
		cout << "operatorLessThanOrEqualTo failed!" << endl;
		return false;
	}
}

bool operatorMoreThanOrEqualTo(){

	Bar b1("a", 1, "cat");
	Bar b2("b", 2, "cat");
	if(b2 >= b1){	
		cout << "operatorMoreThanOrEqualTo passed!" << endl;
		return true;
	}
	else
	{	
		cout << "operatorMoreThanOrEqualTo failed!" << endl;
		return false;
	}
}
//////////////////////////////////////////////// end of bar.h tests

// barchart.h tests
bool testBarchartDefaultConstructor() {

	BarChart bc;
	if(bc.getFrame() != ""){
		cout << "Barchart getFrame() failed!";
		return false;
	}
	else if (bc.getSize() != 0){
		cout << "Barchart getSize() failed!";
		return false;
	}
    cout << "testBarchartDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarchartParamConstructor(){

	BarChart bc(3);
	if(bc.getFrame() != ""){
		cout << "Barchart getFrame() failed!";
		return false;
	}
	else if(bc.getSize() != 0){
		cout << "Barchart getSize() failed!";
		return false;
	}
	cout << "testBarchartParamConstructor: all passed!" << endl;
    return true;
}

bool testBarchartCopyConstructor(){

	BarChart bc(10);
	BarChart bcCopy(bc);
	if(bcCopy.getFrame() != bc.getFrame())
	{
		cout << "Barchart getFrame() failed!";
		return false;
	}
	else if(bcCopy.getSize() != bc.getSize()){
		cout << "Barchart getSize() failed!";
		return false;
	}
	cout << "testBarchartParamConstructor: all passed!" << endl;
    return true;
}

bool testBarchartSetFrame(){

	BarChart bc;
	bc.setFrame("1950");
	if(bc.getFrame() != "1950"){
		cout << "Barchart setFrame() failed!";
		return false;
	}
	cout << "testBarchartSetFrame passed!" << endl;
	return true;
}

bool testBarchartGetFrame(){
	
	BarChart bc;
	if(bc.getFrame() != ""){
		cout << "Barchart getFrame() failed!";
		return false;
	}
	cout << "testBarchartGetFrame passed!" << endl;
	return true;
}

bool testBarchartAddBar(){

	BarChart bc(3);
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	if(bc.getSize() == 0){
		cout << "Barchart getSize() failed!";
		return false;
	}
	cout << "testBarchartAddBar passed!" << endl;
	return true;
}

bool testBarchartAddBarPastCapacity(){

	BarChart bc(3);
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	bc.addBar("San Francisco", 1200, "US");

	if(bc.getSize() != 3){
		cout << "Barchart getSize() failed!";
		return false;
	}
	cout << "testBarchartAddBarPastCapacity passed!" << endl;
	return true;
}

bool testBarchartGetSize(){
	BarChart bc;
	if(bc.getSize() != 0){
		cout << "Barchart getSize() failed!";
		return false;
	}
	cout << "testBarchartGetSize passed!" << endl;
	return true;
}

bool testBarchartBracketOperator(){

	BarChart bc(3);
	bc.setFrame("1950");
	int n = bc.getSize();
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	for (int i = 0; i < n; i++) {
		cout << bc[i].getName() << " ";
		cout << bc[i].getValue() << " ";
		cout << bc[i].getCategory();
		cout << endl;
	}
	return true;
}

void testBarchartGraph()
{
	BarChart bc(3);
	bc.setFrame("1950");
	bc.addBar("Chicago", 1020, "US");
	bc.addBar("NYC", 1300, "US");
	bc.addBar("Paris", 1200, "France");
	string red("\033[1;36m");
	string blue("\033[1;33m");
	map<string, string> colorMap;
	colorMap["US"] = red;
	colorMap["France"] = blue;
	bc.graph(cout, colorMap, 3);
}

void testBCAnimateAddFrameAndAnimate(){
	string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	while(!inFile.eof()){
		bca.addFrame(inFile);
	}
	bca.animate(cout, 12, -1);
}

// barchartanimate.h tests

bool testBCAnimateParamConstuctor(){
	string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	if(bca.getSize() != 0){
		cout << "BarchartAnimate getSize() failed!";
		return false;
	}
	cout << "BarchartAnimate getSize() passed!";
	return true;
}


int main() 
{
	//  bar.h
	cout << "Bar.h tests: " << endl;
	testBarDefaultConstructor();
	testBarParamConstructor();
	testBarGetName();
	testBarGetValue();
	testBarGetCategory();
	operatorLessThan();
	operatorMoreThan();
	operatorLessThanOrEqualTo();
	operatorMoreThanOrEqualTo();

	cout << endl << "////////////////////////////////////////////" << endl << endl;
	
	// barchart.h
	cout << "Barchart.h tests: " << endl;
	testBarchartDefaultConstructor();
	testBarchartParamConstructor();
	testBarchartCopyConstructor();
	testBarchartSetFrame();
	testBarchartGetFrame();
	testBarchartAddBar();
	testBarchartAddBarPastCapacity();
	testBarchartGetSize();
	testBarchartBracketOperator();
	testBarchartGraph();

	cout << endl << "////////////////////////////////////////////" << endl << endl;
	

	// barchartanimate.h tests
	testBCAnimateAddFrameAndAnimate();
	testBCAnimateParamConstuctor();

    return 0;
}