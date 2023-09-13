// bar.h
// TO DO:  add header comment here.  Also add function header comments below.

#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//
// Bar
//
class Bar {

 private:
    string name, category;
    int value;
    
 public:

    // default constructor:
    Bar() 
    {
        name = "";
        value = 0;
        category = "";
    }
    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) 
    {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // destructor:
    virtual ~Bar() 
    {
        // TO DO:  Write this destructor or leave empty if not needed.
    }

    // getName:
	string getName() 
    {        
        return name;
	}

    // getValue:
	int getValue()
    {    
		return value;
	}

    // getCategory:
	string getCategory() 
    {
       return category;
	}

	// operators
    // TO DO:  Write these operators.  This allows you to compare two Bar
    // objects.  Comparison should be based on the Bar's value.  For example:
    
	bool operator<(const Bar &other) const {
        return this->value < other.value;
	}

	bool operator<=(const Bar &other) const {
        return this->value <= other.value;
	}

	bool operator>(const Bar &other) const {
        return this->value > other.value;
	}

	bool operator>=(const Bar &other) const {
        return this->value >= other.value;
	}

};

