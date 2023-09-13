// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Once your three class/abstraction files are completed and tested, run with
// this application to see your final creation.
//
// TO DO: Nothing for the standard application, just compile and run! However,
// before submitting you need to add your creative component.
//
// Adam Koehler
// U. of Illinois, Chicago
// Fall 2022
//
// Original iteration of program developed by:
// Shanon Reckinger
// U. of Illinois, Chicago 

/*
how to run creative component
comment out line 41 and 42
comment out line 62 and comment line 61
this creative component 
is useful since it can modify the playback rate
*/ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {

	string filename;
	int playbackRate;

	cout << "Enter filename: ";
	cin >> filename; 

	// cout << "Enter a playback rate (in thousands): ";
	// cin >> playbackRate;

	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
	
	bca.animate(cout, 12, -1);
	// bca.animate(cout, 12, -1, playbackRate);

    return 0;
}
