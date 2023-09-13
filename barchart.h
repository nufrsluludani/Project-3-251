// barchart.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in graders, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "X";
const string CLEARCONSOLE = "\033[2J";
// const string RESET("\033[0m");


//
// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL
//
// Color codes for light mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for darker mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};



//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string frame;
    
 public:
    
    // default constructor:
    BarChart() 
    {    
        bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
    }
    
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) 
    {    
        bars = new Bar[n];
        capacity = n;
        size = 0;
        frame = "";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
        this->bars = new Bar[other.capacity];    
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        for(int i = 0; i < other.size; i++){
            this->bars[i] = other.bars[i];
        }   
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
        if(this == &other) // handles if we copy ourselves
        {
            return *this;
        }

        delete[] bars; // since we "new" a bar, delete the bar

        // allocate the bar with the same size/capacity
        this->bars = new Bar[other.capacity]; 
        this->size = other.size;
        this->capacity = other.capacity;
        this->frame = other.frame;
        // copy everything from the original bar to the other bar
        for(int i = 0; i < other.size; i++){
            this->bars[i] = other.bars[i];
        }
        
        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() 
    {
        delete[] bars;
        bars = nullptr;
        size = 0;
        capacity = 0;
        frame = "";
    }
    
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart(){
        if(bars != nullptr){
            clear();
        }
    }
    
    // setFrame
    void setFrame(string frame){	
        this->frame = frame; 
    }
    
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {    
        return frame; 
    }
    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) 
    {  
        if(this->size == this->capacity) // check if it goes past the array
        {
            return false;
        }
        Bar b = Bar(name, value, category);
        this->bars[size] = b; // size is the current index of bars
        this->size++; // increment size to move foward
        return true;
    }
    
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() 
    {    
        return size;
    }
    
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i)
    {
        if(i < 0 || i >= this->size)
        {
            __throw_out_of_range("BarChart: i out of bounds");
        }
        else
        {
            return bars[i];
        }
    }
    
    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) 
    {
        sort(bars, bars+size, greater<Bar>()); // sort in descending order
        output << "frame: " << this->frame << endl;
        for(int i = 0; i < this->size; i++)
        {
            output << bars[i].getName() << " " << bars[i].getValue() << " " << bars[i].getCategory() << endl;
        }
    }
    
    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed
                          // for the top bar (max value)
        
        // TO DO: read this example and this erase it.
        // e.g. Here I am plotting 60 red BOXs to output
        string color = "";
        string barstr = "";

        sort(bars, bars+size, greater<Bar>()); // sort descending order

        int topvalue = bars[0].getValue(); // top bar value

        for(int i = 0; i < COLORS.size(); i++)
        {
            for(int j = 0; j < this->size; j++)
            {
                colorMap.insert({bars[j].getCategory(), COLORS[i]}); // associate colors with category
            }
        }

        for(int i = 0; i < top; i++) 
        {
            if(colorMap.count(bars[i].getCategory()) == 1)
            {
                color = colorMap.at(bars[i].getCategory()); // grab catergory if it exists
            }
            barstr = "";
            float bar = (((bars[i].getValue()) * 1.0) / (topvalue * 1.0) * 60.0); // math to be done from jumpstart
            for (int i = 0; i < bar; i++) 
            {
                barstr += BOX;
            }
            output << color << barstr << " " << bars[i].getName() << " " << bars[i].getValue() << endl; // output
        }        
    }
};

