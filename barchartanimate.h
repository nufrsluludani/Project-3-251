// barchartanimate.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;
    int index = 0;
    int amountOfBars = 0;
    
    // this function handles the line and parses it, it grabs each value to be used for adding to a bar and also handles the color 
    void parsingThroughLine(string line, string &year, string &name, string &country, int &value, string &category, BarChart &bc){
        
        stringstream ss(line);
        string temp; // to handle value
        vector<string> values;

        // these set of getlines will get each value within the line 
        getline(ss, year, ','); 
        values.push_back(year);
        getline(ss, name, ',');
        values.push_back(name);
        getline(ss, country, ',');
        values.push_back(country);
        getline(ss, temp, ',');
        values.push_back(temp);
        getline(ss, category, ',');
        values.push_back(category);

        for(int i = 0; i < values.size(); i++)
        {
            year = values.at(0);
            name = values.at(1);
            country = values.at(2);
            value = stoi(values.at(3));
            category = values.at(4);

        }

        value = stoi(temp); // because value is an int, but when we use getline its a string
        bc.addBar(name, value, category); // add to a bar
        bc.setFrame(year);
        
        if(colorMap.count(category) == 0) {
            if(index == 7) { // if it runs out of colors
                index = 0; // reset to loop thru again
            }
            colorMap[category] = COLORS[index]; // category gets a color
            index++; 
        }
    }

    // this function just gets the line that needs to be parsed thru
    void addFrameHelper(ifstream &file)
    {
        string line, year, name, country, category;
        int value, numRecords;
        getline(file, line); // get rid of space
        if(file.eof()){ // if it reaches the end of the file 
            return;
        }
        getline(file, line); // gets the group of records
        numRecords = stoi(line); // holds the line that contains how many records there are
        BarChart bc(numRecords); // will hold a barchart for each group of records
        // a barchart that holds bars so essentially building bars that build into one barchart
        for(int i = 0; i < numRecords; i++){
            getline(file, line); // grabs a line again
            parsingThroughLine(line, year, name, country, value, category, bc);
        }
        this->barcharts[size] = bc;
        this->size++;
    }

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        
        barcharts = new BarChart[4];
        size = 0;
        capacity = 4;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
        index = 0;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        
        delete[] barcharts;
        
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {

        if(this->size == this->capacity){  // handles if barcharts runs out of space
            int newCapacity = capacity * 2;
            BarChart* newBC = new BarChart[newCapacity];

            for (int i = 0; i < this->size; ++i){
                newBC[i] = barcharts[i];
            }

            delete[] barcharts;
            barcharts = newBC;
            capacity = newCapacity;
        }
        addFrameHelper(file);
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 10000;
        int limit;
        if(endIter == -1){ endIter ==  this->size; }
        else{ limit = endIter; }
        for(int i = 0; i < limit; i++){
            top = barcharts[i].getSize();
            usleep(3 * microsecond);
            output << CLEARCONSOLE;
            output << BLACK << title << endl << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
        }        
	}

    // used for creative component, it modifies the playback rate
    void animate(ostream &output, int top, int endIter, int playback) {
		unsigned int microsecond = playback;
        int limit;
        if(endIter == -1){ endIter ==  this->size; }
        else{ limit = endIter; }
        for(int i = 0; i < limit; i++){
            top = barcharts[i].getSize();
            usleep(3 * microsecond);
            output << CLEARCONSOLE;
            output << BLACK << title << endl << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
        }        
	}

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize()
    {        
        return size;   
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i)
    {
        if(i < 0 || i >= this->size)
        {
            __throw_out_of_range("BarChartAnimate: i out of bounds");
        }
        else
        {
            return barcharts[i]; // TO DO:  update this, it is only here so code compiles.
        } 
    }
};
